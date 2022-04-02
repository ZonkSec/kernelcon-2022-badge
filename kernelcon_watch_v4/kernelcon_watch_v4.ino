#include <Wire.h>
#include "src/SSD1106_display/SH1106Wire.h"   
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>
#include "wifi.h"
#include "images.h"
#include "ctf.h"
#include "serial_config.h"
#include "font.h"
#include <ArduinoJson.h>
#include "src/ezTime_lib/ezTime.h"
Timezone Omaha;
#include "src/SSD1106_display/OLEDDisplayUi.h"

SH1106Wire display(0x3c, 5, 4);     // ADDRESS, SDA, SCL
OLEDDisplayUi ui     ( &display );
const char* ssid = wifi_ssid;
const char* password = wifi_pass;
std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

int current_page = 0;
int up = 0;
int down = 0;
int submenu = 0;
int current_next_state = 0;
int lasttextblobfade = 0;
int statetextblobfade = 0;
String data = "";
String messages = "";
bool noData = false;
StaticJsonDocument<12288> doc;
JsonVariant nowTalk;
JsonVariant nextTalk;

//this fuction grabs schedule from AWS.
void getSchedule(){
  HTTPClient http;  //Declare an object of class HTTPClient
  client->setInsecure();
  Serial.println("Fetching data: https://shredder-pw-vault.kernelcon.org/watch_schedule_list.json");
  http.begin(*client,"https://shredder-pw-vault.kernelcon.org/watch_schedule_list.json");
  int httpCode = http.GET();//Send the request
  if (httpCode == 200) { //Check the returning code
    deserializeJson(doc, http.getStream());
  }
  else{
    noData = true;
  }
  http.end();   //Close connection
  //sets this function to run again in 15min
  setEvent(getSchedule,int(UTC.now())+900);
}

//this fuction grabs schedule from AWS.
void getMessages(){
  HTTPClient http;  //Declare an object of class HTTPClient
  client->setInsecure();
  Serial.println("Fetching messages: https://shredder-pw-vault.kernelcon.org/messages.txt");
  http.begin(*client,"https://shredder-pw-vault.kernelcon.org/messages.txt");
  int httpCode = http.GET();//Send the request
  if (httpCode == 200) { //Check the returning code
    messages = http.getString();
  }
  http.end();   //Close connection
  setEvent(getMessages,int(UTC.now())+300);

}

//makes progress bar, takes start and end epcoh
void displayProgressAndTimeRemain(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y, int s, int e){
  int time_end;
  int time_start;
  float dur;
  float elapsed;
  float progress;
  int time_left;
  int tl_min;
  int tl_sec;
  String min_left;
  String sec_left;
  time_end = e;
  time_start = s;
  dur = time_end - time_start;
  elapsed = int(UTC.now())-time_start;
  progress = (elapsed/dur)*100;
  if (progress >= 100){progress = 100;}
  display->drawProgressBar(0+x, 52+y, 90, 10, progress);
 
  time_left = int(dur-elapsed);

  //change secs to min/secs and pad
  tl_min = time_left/60;
  tl_sec = time_left%60;
  if(tl_min <10){min_left = "0"+String(tl_min);  }
  else{min_left = String(tl_min);}
  if(tl_sec <10){sec_left = "0"+String(tl_sec);  }
  else{sec_left = String(tl_sec);}
  if (tl_sec<=0 && tl_min<=0){
    display->drawStringMaxWidth(95+x, 52+y,128, "DONE");
  }
  else{
    display->drawStringMaxWidth(95+x, 52+y,128, min_left+":"+sec_left);
  }
}

//nicely formats and displays time till next 
void displayTimeTill(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y,JsonVariant nextTalk){
    int tl_min = (nextTalk["startUTC"].as<int>() - int(UTC.now()))/60;
    int tl_sec = (nextTalk["startUTC"].as<int>() - int(UTC.now()))%60;
    String min_left;
    String sec_left;
    if(tl_min <10){min_left = "0"+String(tl_min);  }
    else{min_left = String(tl_min);}
    if(tl_sec <10){sec_left = "0"+String(tl_sec);  }
    else{sec_left = String(tl_sec);}
    if (tl_sec<=0 && tl_min<=0){
      display->drawStringMaxWidth(0+x, 52+y,128, nextTalk["length"].as<String>()+"min | Starting soon.");
    }
    else{
      display->drawStringMaxWidth(0+x, 52+y,128, nextTalk["length"].as<String>()+"min | Starts in: " + min_left+":"+sec_left);
    } 
}

//prints talk gist with screen-toggle and line splitting
void displayTalkGist(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y, String gist){
  display->setFont(ArialMT_Plain_10);
  if (gist.length() > 63){
    if (statetextblobfade==0){
      display->drawStringMaxWidth(0+x, 12+y,124,gist.substring(0, 21));
      display->drawStringMaxWidth(0+x, 24+y,124,gist.substring(21, 42));
      display->drawStringMaxWidth(0+x, 36+y,124,gist.substring(42, 63));
    }
    else{
      display->drawStringMaxWidth(0+x, 12+y,124,gist.substring(63, 84));
      display->drawStringMaxWidth(0+x, 24+y,124,gist.substring(84, 105));
      display->drawStringMaxWidth(0+x, 36+y,124,gist.substring(105, 120));
    } 
  }
  else{
    display->drawStringMaxWidth(0+x, 12+y,120, gist);
  }
}

//walks json to gets the current now/next talks for a given track. sets them to global variable
void getNowNextTalks(String trackName){
  int nowtime = int(UTC.now());
  int numOfTalks = doc[trackName].size();
  for (int i = numOfTalks-1; i >= 0; i--) {
    int talkStartUTC = doc[trackName][i]["startUTC"].as<int>();
    if (nowtime > talkStartUTC){
      nowTalk = doc[trackName][i];
      nextTalk = doc[trackName][i+1];
      break;
    }
  }
}

//constant clock overlay
void msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  if (time_format == 24){
    display->drawString(128, 0,Omaha.dateTime("H:i"));
  }
  else{
    display->drawString(128, 0,Omaha.dateTime("h:i"));
  }
  
}

//main page
void mainFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 0, y + 0, kernelcon_width, kernelcon_height, kernelcon_bits);
  display->setFont(Rock_Salt_Regular_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawStringMaxWidth(72+x,7+y,52, "SNACK THE PLANET!"); 
  if (submenu == 0){
    digitalWrite(16,HIGH);
  }
  else{
    digitalWrite(16,LOW);
  }
}

//track1 page
void track1Frame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  getNowNextTalks("bod");
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(Orbitron_Medium_10);
  if (submenu == 0){
    display->drawStringMaxWidth(0+x, 0+y,128, "BoD - Now");
    displayTalkGist(display,state,x,y,nowTalk["gist"].as<String>());
    displayProgressAndTimeRemain(display,state,x,y,nowTalk["startUTC"].as<int>(),nowTalk["endUTC"].as<int>());
   }
   else{
    display->drawStringMaxWidth(0+x, 0+y,128, "BoD - Next");
    displayTalkGist(display,state,x,y,nextTalk["gist"].as<String>());
    displayTimeTill(display,state,x,y,nextTalk);
   }
}

//track2 page
void track2Frame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  getNowNextTalks("tc");
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(Orbitron_Medium_10);
  if (submenu == 0){
    display->drawStringMaxWidth(0+x, 0+y,128, "TC - Now");
    displayTalkGist(display,state,x,y,nowTalk["gist"].as<String>());
    displayProgressAndTimeRemain(display,state,x,y,nowTalk["startUTC"].as<int>(),nowTalk["endUTC"].as<int>());
   }
   else{
    display->drawStringMaxWidth(0+x, 0+y,128, "TC - Next");
    displayTalkGist(display,state,x,y,nextTalk["gist"].as<String>());
    displayTimeTill(display,state,x,y,nextTalk);
   }
}

//viewMessages page
void viewMessages(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(Orbitron_Medium_10);
  display->drawStringMaxWidth(0+x, 0+y,128, "Messages");
  displayTalkGist(display,state,x,y,messages);
}

//interupt handlers for inputs
IRAM_ATTR void UP(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200){
    submenu = 0;
    statetextblobfade = 0;
    lasttextblobfade = int(UTC.now());
    ui.previousFrame();
  }
  last_interrupt_time = interrupt_time;
}
IRAM_ATTR void DOWN(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200){
    submenu = 0;
    statetextblobfade = 0;
    lasttextblobfade = int(UTC.now());
    ui.nextFrame();
  }
  last_interrupt_time = interrupt_time;
}
IRAM_ATTR void SELECT(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200){
    if(submenu == 0){submenu = 1;}
    else{submenu = 0;}
    statetextblobfade = 0;
    lasttextblobfade = int(UTC.now());
  }
  last_interrupt_time = interrupt_time;
}

// This array keeps function pointers to all frames
// frames are the single views that slide in
FrameCallback frames[] = { mainFrame, track1Frame,track2Frame, viewMessages};

// how many frames are there?
int frameCount = 4;

// Overlays are statically drawn on top of a frame eg. a clock
OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  ui.setTargetFPS(30);

	// Customize the active and inactive symbol
  ui.setActiveSymbol(activeSymbol);
  ui.setInactiveSymbol(inactiveSymbol);


  ui.setIndicatorPosition(RIGHT);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_UP);
  ui.setFrames(frames, frameCount);
  ui.setOverlays(overlays, overlaysCount);
  ui.disableAutoTransition();

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();

 // Initialising the UI will init the display too.
  display.init();
  display.resetDisplay();
  display.displayOn();
  display.flipScreenVertically();
  
  display.setContrast(50,241,64);
  display.clear();
  display.drawString(0, 0,"Booting...");
  display.display(); 
  delay(1000);
  
  display.drawString(0, 12,"Connecting to network...");
  display.display(); 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  display.drawString(0, 24,"Connected.");
  display.display(); 
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  display.drawString(0, 36,WiFi.localIP().toString().c_str());
  display.drawString(0, 48,"Syncing time and data...");
  display.display();
  delay(500);

  //using eztime lib, i set TZ and set event to grab schedule from AWS
  Omaha.setLocation("America/Chicago");
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime());
  Serial.println("Omaha: " + Omaha.dateTime());
  getTimeFormatEEPROM();
  setEvent(getSchedule);
  setEvent(getMessages);
  lasttextblobfade = int(UTC.now());
  Serial.println("###############################################");
  Serial.println("## Running. Press any button to configure... ##");
  Serial.println("###############################################");

  //sets up control wheel
  pinMode(12, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(12), UP, FALLING);
  pinMode(13, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(13), DOWN, FALLING);
  pinMode(14, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(14), SELECT, FALLING);

  //setups flashlight
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
}


void loop() {
  //check serial for config/ctf stuff
  if(Serial.available()){
    Serial.read();
    print_welcome();
    config_menu();
  }
 
  //this if is to switch a state for the gist printing function to change
  if ((lasttextblobfade+5) <= int(UTC.now())){
      if (statetextblobfade == 0){statetextblobfade = 1;      }
      else if (statetextblobfade == 1){statetextblobfade = 0;}
      lasttextblobfade = int(UTC.now());
    }
  events(); //this ensures any events get ran (NTP update and AWS schedule)
  int remainingTimeBudget = ui.update();
  //Serial.println(remainingTimeBudget);
  if (remainingTimeBudget > 0) {
    delay(remainingTimeBudget);
  }
}
