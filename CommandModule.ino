
/*
  
  The Command Module - "every dangerous futuristic invention needs The Command Module" 
  Dan Ray antfriend@gmail.com
  12/15/2013
  
  This program wraps up verbal interactivity and visual (LED) status, with a simple parallel binary status out for controlling other hardware.

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the 
  public domain worldwide. This software is distributed without any warranty.

  You should have received a copy of the CC0 Public Domain Dedication
  along with this software.
  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/
#include <SoftwareSerial.h>

#define vrrxPin 4    // Serial input (connects to Emic 2 SOUT)10
#define vrtxPin 5    // Serial output (connects to Emic 2 SIN)11
SoftwareSerial vr_serial = SoftwareSerial(vrrxPin,vrtxPin);//vr

#define rxPin 2    // Serial input (connects to Emic 2 SOUT)
#define txPin 3    // Serial output (connects to Emic 2 SIN)

SoftwareSerial t2s_serial =  SoftwareSerial(rxPin, txPin);

#include <EasyVR.h>
EasyVR easyvr(vr_serial);
//Groups and Commands
enum Groups
{
  GROUP_1  = 1,
};

enum Group1 
{
  G1_LEARN = 0,
  G1_GO = 1,
};

EasyVRBridge bridge;
int8_t group, idx;

void listening()
{
  if(!vr_serial.isListening())
  {
    vr_serial.listen();
  }
}

void speaking()
{
  if(!t2s_serial.isListening())
  {
    t2s_serial.listen();
  }
}

void setup()  // Set up code called once on start-up
{
  L_setup();
  T2S_setup();//can't say anything before initiating the bridge check - or bridge won't work
  //saynumber(100);
  //saynumber(0);
  //saynumber(1);
  //T2S_yes();
  //T2S_test();
  //T2S_all_voices();
  //T2S_sing_daisy();
    
  VR_setup();

  //T2S_flush();
  long random_seed = analogRead(5);
  randomSeed(random_seed);
  saynumber(random_seed);
  //T2S_hello();
}

void action();

void loop_until_trigger_spoken()
{
  int the_group = EasyVR::TRIGGER; //<-- start group (customize)
  int heard = 0;
  while(heard != 1)
  {
    heard = VR_listening_for_group(the_group);
    /*
    switch (heard) {
      case 0:
        say("Case 0.");
        
        
        break;
      case 1:
        say("Case 1.");
        the_group = GROUP_1;
        
        //T2S_hello();
        break;
      default: 
          say("Default case.");
          saynumber(heard);
          //T2S_hello();
          break;
        // if nothing else matches, do the default
        // default is optional
    }
  */    
  } 
}

void listen_for_GROUP_1()
{
  //int the_group = EasyVR::TRIGGER; //<-- start group (customize)
  int heard = 0;
  //while(heard != 2)
  //{
    heard = VR_listening_for_group(GROUP_1);
    saynumber(heard);
    
    switch (heard) {
      case 0:
        say("Are you going to say something?");
        heard = VR_listening_for_group(GROUP_1);//timed out try again
 
        break;
      case 2:
        say("So what?");
        //the_group = GROUP_1;
        
        //T2S_hello();
        break;
      default: 
          //say("Default case.");
          //saynumber(heard);
          //T2S_hello();
          break;
        // if nothing else matches, do the default
        // default is optional
    }
      
  //} 
}

void listen_for_Action()
{
  //int the_group = EasyVR::TRIGGER; //<-- start group (customize)
  int heard = 0;
  //while(heard != 2)
  //{
    heard = VR_listening_for_word(EasyVR::ACTION_SET);
    saynumber(heard);
    
    switch (heard) {
      case 0:
        say("Are you going to say something?");
        heard = VR_listening_for_group(EasyVR::ACTION_SET);//timed out try again
 
        break;
      case 2:
        say("So what?");
        //the_group = GROUP_1;
        
        //T2S_hello();
        break;
      default: 
          //say("Default case.");
          //saynumber(heard);
          //T2S_hello();
          break;
        // if nothing else matches, do the default
        // default is optional
    }
      
  //} 
}

void random_response_for_robot()
{
  long randNumber = random(6);
    switch (randNumber) {
      case 0:
        say("Yes?");        
        break;
      case 1:
        say("Human!");
        break;
      case 2:
        say("What?");
        break;
      case 3:
        say("That is my name, don't wear it out.");
        break;
      case 4:
        say("Hi.");
        break;
      case 5:
        say("Hello.");
        break;
      case 6:
        say("What do you want?");
        break;
      default: 
          say("You are number.");
          saynumber(randNumber);
          break;
    }  
  //say("human.");
}

void loop()  // Main code, to run repeatedly
{ 
  //say("Listening.");
  loop_until_trigger_spoken();
  random_response_for_robot();//listen for the trigger
  //listen_for_GROUP_1();
  listen_for_Action();
  
  //heard = VR_listening(the_group);
  
  
  //VR_loop();
  //T2S_all_voices();

  //delay(500);    // 1/2 second delay
    
  //T2S_sing_daisy();
  /*
  while(1)      // Demonstration complete!
  {
    delay(500);
    L_LED_on();
    delay(500);              
    L_LED_off();
  }
  */
}

void VR_setup()
{
  pinMode(vrrxPin, INPUT);
  pinMode(vrtxPin, OUTPUT);
  
  // bridge mode?
  if (bridge.check())
  {
    //speaking();//talking will mess up the bridge
    //T2S_bridge_on();//talking will mess up the bridge
    listening();
    cli();
    bridge.loop(0, 1, vrrxPin, vrtxPin);
  }
  
  vr_serial.begin(9600);//once this port begins, the next message from T2S will END the program upon completion
  listening();

  if (!easyvr.detect())
  {
    say("No voice recognition module detected!");
    for (;;);
  }
  easyvr.setTimeout(5);
  easyvr.setLanguage(0);//easyvr.setLanguage(EasyVR::JAPANESE);
}

int VR_listening_for_word(int group)
{
 //recognizeWord
  //easyvr.recognizeCommand(group);
  easyvr.recognizeWord(group);
  return VR_listening(group);
}

int VR_listening_for_group(int group)
{
  easyvr.recognizeCommand(group);
  return VR_listening(group);
}

int VR_listening(int group)
{
  //easyvr.recognizeCommand(group);
  do
  {
    // can do some processing while waiting for a spoken command
  }
  while (!easyvr.hasFinished());
  idx = easyvr.getWord();
  //saynumber(idx);
  if (idx >= 0)
  {
    // built-in trigger (ROBOT)
    //T2S_yes();
    // group = GROUP_X; <-- jump to another group X
    return 1;
  }
  idx = easyvr.getCommand();
  if (idx >= 0)
  {
    uint8_t train = 0;
    char name[32];
    //saynumber(idx);
    if (easyvr.dumpCommand(group, idx, name, train))
    {
      say(name);
      return 2;
    }
    else
    {
      say("Going to action.");
      action();
      return 3;
    }
    //easyvr.playSound(0, EasyVR::VOL_FULL);
    // perform some action
    
  }
  else // errors or timeout
  {
    if (easyvr.isTimeout())
    {
      //say("Are you going to say something?");
      return 0;
    }
    /*
    if (easyvr.isTimeout())
      T2S_times_up();
      //Serial.println("Timed out, try again...");
    */
    int16_t err = easyvr.getError();
    if (err >= 0)
    {
      say("Error number.");
      saynumber(err);
    }
  }
  return idx;
}

void action()
{
    T2S_action();
    say("Action group.");
    saynumber(group);
    say("I D X.");
    saynumber(idx);
    
    switch (group)
    {
    case GROUP_1:
      switch (idx)
      {
      case G1_LEARN:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G1_GO:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    }
}
