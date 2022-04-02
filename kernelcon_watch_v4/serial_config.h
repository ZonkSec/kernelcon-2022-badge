#include <EEPROM.h>
#define EEPROM_SIZE 12

#include "src/Adafruit_NeoPixel-1.7.0/Adafruit_NeoPixel.h"
Adafruit_NeoPixel strip { 1, 15, NEO_GRB + NEO_KHZ800 };


void set_rgb(){
  strip.begin();
  String redLED;
  String grnLED;
  String bluLED;
  Serial.println("WARNING: Enabling RGB LED results in shorter battery life.");
  Serial.println("...but it looks awesome!");
  Serial.print("Red LED Value (0-255): ");
  while(!Serial.available() ){}
  redLED = Serial.readStringUntil('\r');
  Serial.println();

  Serial.print("Green LED Value (0-255): ");
  while(!Serial.available() ){}
  grnLED = Serial.readStringUntil('\r');
  Serial.println();

  Serial.print("Blue LED Value (0-255): ");
  while(!Serial.available() ){}
  bluLED = Serial.readStringUntil('\r');
  Serial.println();

  for (size_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, redLED.toInt(), grnLED.toInt(), bluLED.toInt());
  }
  strip.show();
}


int time_format = 12;
void getTimeFormatEEPROM(){
  EEPROM.begin(12);
  EEPROM.get(0, time_format);
  EEPROM.end();
}

void print_welcome(){
  Serial.println(F(""));
  Serial.println(F("KERNELCON-2022"));
  Serial.println(F(" __      __         __         .__     "));
  Serial.println(F("/  \\    /  \\_____ _/  |_  ____ |  |__  "));
  Serial.println(F("\\   \\/\\/   /\\__  \\\\   __\\/ ___\\|  |  \\ "));
  Serial.println(F(" \\        /  / __ \\|  | \\  \\___|   Y  \\"));
  Serial.println(F("  \\__/\\  /  (____  /__|  \\___  >___|  /"));
  Serial.println(F("       \\/        \\/          \\/     \\/ "));
  Serial.println(F("            CONFIGURATION SYSEM  v1.3.37"));
  Serial.println(F(""));
  Serial.println(F("CODED WITH <3 BY @ZONKSEC"));
  Serial.println(F(""));
  Serial.println(F("COMMANDS:"));
  Serial.println(F(""));
  Serial.println(F("STF    = set time format (12h or 24h)"));
  Serial.println(F("AWS    = dump AWS configuration"));
  Serial.println(F("CLR    = set RGB color"));
  Serial.println(F("ETS    = enter the sewers..."));
  Serial.println(F("HELP   = displays this menu"));
  Serial.println(F("EXIT   = exits configuration"));
  Serial.println(F(""));
}

void set_time_format(){
    Serial.print("Select time format (12h or 24h): ");
    while(!Serial.available() ){}
    input ="";
    input = Serial.readStringUntil('\r');
    Serial.println(input);
    if (input == "12h" || input == "12"){
      EEPROM.begin(12);
      EEPROM.put(0, 12);
      EEPROM.commit();
      EEPROM.end();
      time_format = 12;
      Serial.println("12h selected");
    }
    else if (input == "24h" || input == "24"){
      EEPROM.begin(12);
      EEPROM.put(0, 24);
      EEPROM.commit();
      EEPROM.end();
      time_format = 24;
      Serial.println("24h selected");
    }
    else{
      Serial.println("Invalid selection");
    }
}

bool exit_bool = false;
void config_menu(){
  do {
    Serial.print("CONFIG> ");
    while(!Serial.available() ){}
    input ="";
    input = Serial.readStringUntil('\r');
    Serial.print("CONFIG> ");
    Serial.println(input);
    if (input == "STF" || input == "stf"){
      set_time_format();
    }
    else if (input == "HELP" || input == "help"){
      print_welcome();
    }
    else if (input == "AWS" || input == "aws"){
      Serial.println("AWS_ACCESS_KEY_ID = AKIAUAZHHZ5QBHME2MWJ");
      Serial.println("AWS_SECRET_ACCESS_KEY = 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");
    }
    else if (input == "ETS" || input == "ets"){
      clearscreen();
      print_welcome_ctf();
      while(!Serial.available() ){}// wait for enter to be pressed
      if(Serial.available()){Serial.read();}//read the the enter to get off buffer, then start level 1
      lvl_1();
    }
    else if (input == "CLR" || input == "clr"){
      set_rgb();
    }
    else if (input == "EXIT" || input == "exit"){
      Serial.println("Exiting...");
      clearscreen();
      exit_bool = true;
    }
    else {
      Serial.println("UKNOWN COMMAND");
    }
  } 
  while(exit_bool == false);
}
