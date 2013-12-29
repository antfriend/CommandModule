
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
  GROUP_2  = 2,
  GROUP_3  = 3,
};

enum Group2 
{
  G2_HELP = 0,
  G2_SPEAK = 1,
  G2_VOICE = 2,
  G2_LEARN = 3,
  G2_SING = 4
};

enum Group3 
{
  G3_CHIENESE = 0,
  G3_ENGLISH = 1,
  G3_DAISY = 2,
  G3_KLINGON = 3,
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
  L_red_off();
  T2S_hello();
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


//void action();

void loop_until_trigger_spoken()
{
  int the_group = EasyVR::TRIGGER; 
  int heard = 0;
  while(heard != 99)
  {
    heard = VR_listening_for_group(the_group);
  } 
}

void listen_for_GROUP_3()
{
    int heard = 0;
    heard = VR_listening_for_group(GROUP_3);

    switch(heard)
    {
        case G3_CHIENESE:
          say("Nee how.");
          break;
        case G3_ENGLISH:
          say("Hello.");
          break;
        case G3_DAISY:
          T2S_sing_daisy();
          break;
        case G3_KLINGON:
          say("Dole! Bot! Kuchat!");
          break;
        default:
          say("I don't know how to say that");
          break;      
    }
    
}

void listen_for_GROUP_2()
{
    int heard = 0;
    heard = VR_listening_for_group(GROUP_2);
    //saynumber(heard);
    
    switch(heard)
    {
      case G2_HELP:
         say("Command options are.  Speak.  Voice.  Learn.  Sing.  And help.");
         break;
      case G2_SPEAK:
         //listen for what to say
         listen_for_GROUP_3();
         break;
      case G2_VOICE:
         //listen for number
         heard = VR_listening_for_word(EasyVR::NUMBER_SET);
         //say("You said.");
         T2S_use_voice(heard);
         //saynumber(heard);
         break;
      case G2_LEARN:
         say("I am ready to learn.");
         break;
      case G2_SING:
         T2S_sing_daisy();
         break;
      default:
         T2S_random_8_ball_response();
         break; 
    }
    /*
    switch (heard) 
    {
      case 0:
        say("Case 0");
        heard = VR_listening_for_group(GROUP_2);//timed out try again
 
        break;
      case 2:
        say("case 2");
        //the_group = GROUP_1;
        
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

void listen_for_Action()
{
    int heard = 0;
    heard = VR_listening_for_word(EasyVR::ACTION_SET);
    
    switch (heard) {
      case -1:
        //heard = VR_listening_for_word(EasyVR::ACTION_SET);//timed out try again
        //say("I don't understand.");
        //random 8 ball response
        T2S_random_8_ball_response();
        break;
      case 0://Action
        say("Action!");
        break;
      case 1://Move
        say("Move what?");
        break;
      case 2://Turn
        say("Turn what?");
        break;
      case 3://Run
        say("Run what?");
        break;
      case 4://Look
        say("I have no optical sensors.");
        break;
      case 5://Attack
        say("Attack!");
        break;
      case 6://Stop
        say("Stop!");
        break;
      case 7://Hello
        say("Hello there, nice to meet you.");
        break;
        
      default: 
          say("Default case.");
          //saynumber(heard);
          //T2S_hello();
          break;
        // if nothing else matches, do the default
        // default is optional
    }
      
  //} 
}

void loop()  // Main code, to run repeatedly
{ 
  //say("Listening.");
  loop_until_trigger_spoken();
  T2S_random_response_for_robot();//listen for the trigger
  listen_for_GROUP_2();
  //listen_for_Action();built-in wordset
  
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

int VR_listening_for_word(int group)
{
  easyvr.recognizeWord(group);
  do
  {
    // can do some processing while waiting for a spoken command
  }
  while (!easyvr.hasFinished());
  idx = easyvr.getWord();
  //saynumber(idx);
  if (idx >= 0)
  {
    return idx;
  }
  else // errors or timeout
  {
    if (easyvr.isTimeout())
    {
      //say("Are you going to say something?");
      return -1;
    }
    /*
    if (easyvr.isTimeout())
      T2S_times_up();
      //Serial.println("Timed out, try again...");
    */
    int16_t err = easyvr.getError();
    if (err >= 0)
    {
      //say("Error number.");
      //saynumber(err);
    }
  }
  return idx;
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
    return 99;
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
      return idx;
    }
    else
    {
      say("Going to action.");
      //action();
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
      //say("Error number.");
      //saynumber(err);
    }
  }
  return idx;
}

/*  
void action()
{
    T2S_action();
    say("Action group.");
    saynumber(group);
    say("I D X.");
    saynumber(idx);
  
    switch (group)
    {
    case GROUP_2:
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
*/
