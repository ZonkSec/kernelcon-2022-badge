//variables for serial game
String input;
char lvl_1_ans[7] = "rrrddr";
char lvl_2_ans[187] = "rddddddddrrddllddrrrruuuurrddddrruuuuuurrddrruurruurrrruurruurrddddllddddddrruurrddddllllddddddrruuuurrddrruurrrruuuulllluurruulllluuuuuurrrrrrddrruurrddddrruuuurrddddddddllddrrddddddddr";
char lvl_3_ans[183] = "rddrruurrddddllddrrrrrrddllllllllddddrrddllddrrddrrrruurruurrrruulluurruulluuuulllluuuurrddrrrruurrrrrrddddrruurrrrddddddddlluullllddlluullddddddddllddrrrrrrrrrruurrddrrrrrrrrrrrrrrr";

int checker(String answer, int len){
      for (int x = 0; x < len;){
        Serial.println("What direction? (up=u, down=d, right=r, left=l)");
        while(!Serial.available() ){}
        input ="";
        input = Serial.readStringUntil('\r');
        if (input[0] == answer[x]){
            x++;
        }
        else{
            Serial.print("Wrong way pal!" );
            if(Serial.available()){Serial.read();}
            return 0;
        }
    }
    return 1;
  
}


void clearscreen(){
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");     // cursor to home command
}
void printlvl_1(){
  clearscreen();
  Serial.println("");
  Serial.println("+-+-+");
  Serial.println("#   |");
  Serial.println("+-+ +");
  Serial.println("|    ");
  Serial.println("+-+-+");
  Serial.println("");
}
void printlvl_2(){
  clearscreen();
  Serial.println(F(""));
  Serial.println(F("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"));
  Serial.println(F("#   |   |     |     |   |       |   |   |"));
  Serial.println(F("+ + +-+ + +-+ +-+ + + + + +-+ + + + + + +"));
  Serial.println(F("| |     |   |     |   | | |   |   | | | |"));
  Serial.println(F("+ +-+-+-+ + +-+-+-+ +-+ + + +-+-+-+ + + +"));
  Serial.println(F("| |       |   |     |   | |       |   | |"));
  Serial.println(F("+ + +-+-+-+-+-+ +-+-+ +-+ +-+-+-+ +-+ + +"));
  Serial.println(F("| |     |   |   |   | | |     |   |   | |"));
  Serial.println(F("+ +-+-+-+ + + + +-+ + + +-+-+ + +-+-+-+ +"));
  Serial.println(F("|   |   | |   | |   | |   |   |     |   |"));
  Serial.println(F("+-+ + + + +-+-+ + +-+ + + + +-+-+-+ + +-+"));
  Serial.println(F("|   | | | |     |       | |     |   |   |"));
  Serial.println(F("+ +-+ + + +-+-+-+-+-+-+-+ +-+-+ + +-+ + +"));
  Serial.println(F("|     |   |     |   |         | | | | | |"));
  Serial.println(F("+-+-+ +-+-+ +-+ + + + +-+-+-+-+ + + + + +"));
  Serial.println(F("|     |   | | | | | | |   |     | |   | |"));
  Serial.println(F("+ +-+-+-+ + + + + + + + + + +-+-+ +-+-+ +"));
  Serial.println(F("|   |       |     | | | |   |   |     | |"));
  Serial.println(F("+-+ +-+-+ +-+-+-+-+ + + +-+-+-+ +-+-+ + +"));
  Serial.println(F("|         |         |   |             |  "));
  Serial.println(F("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"));
  Serial.println(F(""));
  }
void printlvl_3(){
  clearscreen();
  Serial.println(F(""));
  Serial.println(F("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"));
  Serial.println(F("  |   |     |       |       |       |   |"));
  Serial.println(F("+ + + + + +-+ +-+-+ +-+-+-+ + +-+-+ + + +"));
  Serial.println(F("|   | | |     |   | |     |   |   |   | |"));
  Serial.println(F("+ +-+ + +-+-+-+-+ + + +-+ +-+-+ + +-+-+ +"));
  Serial.println(F("| |   |     |     |   |       | |   |   |"));
  Serial.println(F("+ + +-+-+-+ + +-+-+-+-+ + +-+ + +-+ + +-+"));
  Serial.println(F("| |       | |           | | | | |   |   |"));
  Serial.println(F("+-+-+-+-+ + +-+-+-+-+-+-+ + + + + +-+-+ +"));
  Serial.println(F("|         |   |   |     | |   | | |     |"));
  Serial.println(F("+ +-+-+-+-+-+ + + + +-+ + +-+ + + + +-+-+"));
  Serial.println(F("| | |   | |   | |   | |   |   | |   |   |"));
  Serial.println(F("+ + + + + + +-+ +-+-+ +-+-+-+ + +-+-+ + +"));
  Serial.println(F("|   | | | |   | |     |     | |   | | | |"));
  Serial.println(F("+-+ + + + +-+ + + + +-+-+-+ + +-+ + + +-+"));
  Serial.println(F("|   | |       | | | |         |   | |   |"));
  Serial.println(F("+ +-+ +-+ +-+-+ + +-+ +-+-+-+-+ +-+ +-+ +"));
  Serial.println(F("|   | |   |     |     |   |           | |"));
  Serial.println(F("+-+ +-+ +-+ + +-+-+-+-+ + + +-+-+-+-+-+ +"));
  Serial.println(F("|       |   |           |                "));
  Serial.println(F("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"));
  Serial.println(F(""));
  }
void print_welcome_ctf(){
  clearscreen();
  Serial.println(F("              ,;;;!!;;"));
  Serial.println(F("        ,;<!!!!!!!!!!!;"));
  Serial.println(F("     `'<!!!!!!!!!!(``'!!"));
  Serial.println(F("           ,;;;;;;, `\\. `\\         .,c$$$$$$$$$$$$$ec,."));
  Serial.println(F("      ,;;!!!!!!!!!!!>; `. ,;!>> .e$$$$$$$$\\\"\".  \"?$$$$$$$e."));
  Serial.println(F(" <:<!!!!!!!!'` ..,,,.`` ,!!!' ;,(?\"\"\"\"\"\"\";!!''<; `?$$$$$$PF ,;,"));
  Serial.println(F("  `'!!!!;;;;;;;;<!'''`  !!! ;,`'``''!!!;!!!!`..`!;  ,,,  .<!''`)."));
  Serial.println(F("     ```'''''``         `!  `!!!!><;;;!!!!! J$$b,`!>;!!:!!`,d?b`!>"));
  Serial.println(F("                          `'-;,(<!!!!!!!!!> $F   )...:!.  d\"  3 !>"));
  Serial.println(F("                              ```````''<!!!- \"=-='     .  `--=\",!>"));
  Serial.println(F("                         .ze$$$$$$$$$er  .,cd$$$$$$$$$$$$$$$$bc.'"));
  Serial.println(F("                      .e$$$$$$$$$$$$$$,$$$$$$$$$$$$$$$$$$$$$$$$$$."));
  Serial.println(F("                     z$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$c ."));
  Serial.println(F("                    J$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$c"));
  Serial.println(F("                    $$$$$$$$$$$$$$P\"`?$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$b"));
  Serial.println(F("                    $$$$$$$$$$$$$$ dbc `\"\"?$$$$$$$$$$$$$$$$$$$$$$?$$$$$$$c"));
  Serial.println(F("                    ?$$$$$$$$$$$$$$$$$$c.      \"\"\"\"????????\"\"\"\" c$$$$$$$$P"));
  Serial.println(F("         .,,.        \"$$$$$$$$$$$$$$$$$$$$c.   ._              J$$$$$$$$$"));
  Serial.println(F(" .,,cc$$$$$$$$$bec,.  `?$$$$$$$$$$$$$$$$$$$$$c.```%%%%,%%%,   c$$$$$$$$P\""));
  Serial.println(F("$$$$$$$$$$$$$$$$$$$$$$c  \"\"?$$$$$$$$$$$$$$$$$$$$$bc,,.`` .,,c$$$$$$$P\"\",cb"));
  Serial.println(F("$$$$$$$$$$$$$$$$$$$$$$$b bc,.\"\"??$$$$$$$$$$$$$$FF\"\"?????\"\",J$$$$$P\" ,zd$$$"));
  Serial.println(F("$$$$$$$$$$$$$$$$$$$$$$$$ ?$???%   `\"\"??$$$$$$$$$$$$bcucd$$$P\"\"\"  ==$$$$$$$"));
  Serial.println(F("$$$$$$$$$$$$$$$$$$$$$$$P\" ,;;;<!!!!!>;;,. `\"\"\"\"??????\"\"  ,;;;;;;;;;, `\"?$$"));
  Serial.println(F("$$$$$$$$$$$$$$$$$$$P\"\",;!!!!!!!!!!!!!!!!!!!!!!!;;;;;;!!!!!!!!!!!!!!!!!;  \""));
  Serial.println(F("$$$$$$$$$$$$$$$$$\"\",;!!!!!!'``.,,,,,.```''!!!!!!!!!!!!!!!!!!!!'''''!!!!!>"));
  Serial.println(F("$$$$$$$$$$$$$$$\" ;!!!!!'`.z$$$$$$$$$$$$$ec,. ```'''''''``` .,,ccecec,`'!!!"));
  Serial.println(F("$$$$$$$$$$$$$\" ;!!!!' .c$$$$$$$$$$$$$$$$$$$$$$$c  :: .c$$$$$$$$$$$$$$$. <!"));
  Serial.println(F("$$$$$$$$$$$\" ;!!!!' .d$$$$$$$$$$$$$$$$$$$$$$$$$$b ' z$$$$$$$$$$$$$$$$$$c <"));
  Serial.println(F("$$$$$$$$$F  <!!!'.c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$b  $$$$$$$$$$$$$$$$$$$$r"));
  Serial.println(F("$$$$$$$P\" <!!!' c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$, \"$$$$$$$$$$$$$$$$$$$$"));
  Serial.println(F("$$$$$P\" ;!!!' z$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  $$$$$$$$$$$$$$$$$$$"));
  Serial.println("");
  Serial.println("kernel{021f9f5091f4895db9c6306194b35965}");
  Serial.println("");
  Serial.println("Welcome to the sewers fellow turtle!");
  Serial.println("We must get through the sewer to find Shredder!");
  Serial.println("The entrance is on the top left (#). The exit is bottom right.");
  Serial.println("Press enter to begin if you dare...");
}

void finished(){
  clearscreen();
  Serial.println("You've escaped the sewers!");
  Serial.println("kernel{2d86bd78aad5cbc3b726606d6b83aab0}");
  Serial.println("You are met with the entrance to Shredder's lair.");
  Serial.println(F("!  !  !  !  !  !  !  !  !  ! !  !  !  !  !  !  !  !  !  !"));
  Serial.println(F("I__I__I__|__I__I__I__I__|__I_I__I__I__|__I__I__I__I__|__|"));
  Serial.println(F("|--|--|--|--|--|--|--|--|--|-|--|--|--|--|--|--|--|--|--|"));
  Serial.println(F("|__|__|__| _|__| _|__|__| _|_| _|__|__| _|__| _|__|__| _|"));
  Serial.println(F("|--|--|--|--|--|----------------------|--|--|--|--|--|--|"));
  Serial.println(F("|  |  |  |  |  |                      |  |  |  |  |  |  |"));
  Serial.println(F("|  |  |  |  |  |                      |  |  |  |  |  |  |"));
  Serial.println(F("|  |  |  |  |  |  Username: Shredder  |  |  |  |  |  |  |"));
  Serial.println(F("|  |  |  |  |  |  Password:_________  |  |  |  |  |  |  |"));
  Serial.println(F("|  |  |  |  |  |                      |  |  |  |  |  |  |"));
  Serial.println(F("|  |  |  |  |  |                      |  |  |  |  |  |  |"));
  Serial.println(F("|  |  |  |  |  | hint: aws            |  |  |  |  |  |  |"));
  Serial.println(F("|__|__|__|__|__|______________________|__|__|__|__|__|__|"));
  Serial.println(F("|--|--|--|--|--|--|--|--|--|-|--|--|--|--|--|--|--|--|--|"));
  Serial.println(F("|__|__|__|__|__|__|__|__|__|_|__|__|__|__|__|__|__|__|__|"));
  Serial.println(F("|--|--|--|--|--|--|--|--|--|-|--|--|--|--|--|--|--|--|--|"));
  Serial.println(F("|--|--|--|--|--|--|--|--|--|-|--|--|--|--|--|--|--|--|--|"));
  Serial.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
  Serial.println("But it's password protected...");
  Serial.println("What is Shredder's password?");
  while(!Serial.available() ){}
  input ="";
  input = Serial.readStringUntil('\r');
  if (input == "turtlesoup"){
    Serial.println("You're in! (⌐■_■)" );
    Serial.println(F("                      .;iiiiii;;."));
    Serial.println(F("                  ;i!!!!!!!!!!!!!!!i."));
    Serial.println(F("               .i!!!!!!!!!'`.......`''="));
    Serial.println(F("              i!!!!!!!!' .:::::::::::::.."));
    Serial.println(F("             i!!!!!!!!' :::::::::::::::::::."));
    Serial.println(F("          ' i!!!!!!!!' :::::::::::::::::::::::."));
    Serial.println(F("         :  !!!!!!!!! ::::::::::::::::::::::::::."));
    Serial.println(F("        ::  !!!!!!!! ::::::::::::::::::::::::::::::"));
    Serial.println(F("       ::: <!!!!!!!! ::::::::::::::::::::::::::::::: i!!!!>"));
    Serial.println(F("      .::: <!!!!!!!> ::::::::::::::::::::::::::::'` i!!!!!'"));
    Serial.println(F("      :::: <!!!!!!!> ::::::::::::::::::::::::'`  ,i!!!!!!'"));
    Serial.println(F("      :::: `!!!!!!!> :::::::::::::::::::''`  ,i!!!!!!!!'.."));
    Serial.println(F("     `::::  !!!!!!!!.`::::::::::::::'` .,;i!!!!!!!!!!' ::::."));
    Serial.println(F("      ::::  !!!!!!!!!, `''''```  .,;ii!!!!!!!!!!!'' .::::::::"));
    Serial.println(F("  i!; `::' .!!!!!!!!!!!i;,;i!!!!!!!!!!!!!!!!!!' .::::::::::::::"));
    Serial.println(F(" i!!!!i;,;i!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!''`  ::::::::::::::::::"));
    Serial.println(F(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'`..euJB$. ::::::::::::::::' ::."));
    Serial.println(F("  !!!!!!!!!!!!!!!!!!!!!!!!!!!''`,   $$$$$$$$$Fc :::::::::::::: .:::::"));
    Serial.println(F("    `''''''''''''''''` ..z e$$$F   d$P\"`\"\"??<<3c :::::::::::' ::::::::."));
    Serial.println(F("       :::: ?Fx$b. \"?$ $$$b($$\"   dF   'ud$$$$$$c `:::::::' .:::::::::::"));
    Serial.println(F("       `:::  $$$$$r-.  P9$$$?$bedE' .,d$$$$$$$P\"   `::::' .:::::::::::::"));
    Serial.println(F("        :::: `? =       \"\"\"\"   \"\"?????????\"\"  .~~~.  :'.:::::::::::::::' ;"));
    Serial.println(F("        :::::  $$$eeed\" .~~~~~~~~~~~~~~~~~~~~~~~~~~~  ::::::::::::::::' i!"));
    Serial.println(F("        :::::  $$$PF\" .~~.$.~~~~~~~~~~~~~~~~~~~~~~~~.  :::::::::::::' ,!!!"));
    Serial.println(F("         ::       .~~~~~~ ?$ ~~~~~~~~~~~~~~~~~~~~~~~~.  ::::::::::'  ;!!!!"));
    Serial.println(F("          ::  ~~~~~~~~~~~.`$b ~~~~~~~~~~~~~~~~~~~~~~~~. `:::::::'  ;!!!!!'"));
    Serial.println(F("         `:::  ~~~~~~~~~~~ `$L ~~~~~~~~~~~~~~~~~~~~~~~ .  `''`   ;!!!!!!"));
    Serial.println(F("          ::::  ~~~~~~~~~~~ `$c'~~~~~~~~~~~~~~~~~~~~~ ~~ ,iiii! i!!!!!!  !"));
    Serial.println(F("          :::::  ~~~~~~~~~~~ \"$c`~~~~~~~~~~~~~~~~~~~ ~~ ;!!!!' i!!!!!!  i!"));
    Serial.println(F("          `:::::  ~~~~~~~~~~~ `$.`~~~~~~~~~~~~~~~~  ~  <!!!!' ;!!!!!!'  !!"));
    Serial.println(F("           :::'`   `~~~~~~~~~~ \"$.`~~~~~~~~~~~~~~ .~ .!!!!!' ;!!!!!!!  i!!"));
    Serial.println(F("              ,i!    ~~~~~~~~~~ \"$r'~~~~~~~~~~~~ '  ;!!!!!  ;!!!!!!!!  !!!"));
    Serial.println(F("             !!!!i !i. `~~~~~~~~ `$c ~~~~~~~~~~~~  <!!!!'  i!!!!!!!!!  !!!"));
    Serial.println(F("             :!!!!> !!!;  ~~~~~~~. \"$. ~~~~~~~~ .;!!!!'  ;!!!!!!!';!!  `!!"));
    Serial.println(F("             `!!!!! `!!!!;.  ~~~~~~~~~~~~~~  .;i!!!!' .i!!!!!!' ,!!!!i  !!"));
    Serial.println(F("              !!!!!!; `!!!!!i;. ~~~~~~~ .;i!!!!''`.;i!!!!!!!'.;!!!!!!!>  !"));
    Serial.println(F("          :!  !!!!!!!i `'!!!!!!!!!!!!!!!'''`.;ii!!!!!'`.'` ;!!!!!!!!!!   '"));
    Serial.println("kernel{780c4852ba12fd73f7dbd0e6b6df19fa}");
    Serial.println("Finish the fight at shredderlair-e9c3acf5a4cd0.kernelcon.org");
    Serial.println("Press enter to go back to config...");
    while(!Serial.available() ){}
  }
  else{
    Serial.print("Wrong! Back to the start!" );
    while(!Serial.available() ){}
  }
}
void lvl_3() {
  printlvl_3();
    if (1 == checker(lvl_3_ans,182)){
      finished();
    }
    else{
      return;
    }
  }
void lvl_2() {
  printlvl_2();
    if (1 == checker(lvl_2_ans,186)){
      lvl_3();
    }
    else{
      return;
    }
  }
void lvl_1() {
    printlvl_1();
    if (1 == checker(lvl_1_ans,6)){
      lvl_2();
    }
    else{
      return;
    }
  }
