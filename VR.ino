/*
  
  VR - a voice recognition software module for the EasyVR hardware module
                                                         
  Dan Ray antfriend@gmail.com
  12/15/2013
  adapted from:
  Example code for the EasyVR library v1.3
  Written in 2013 by RoboTech srl for VeeaR <http:://www.veear.eu>
  
  This module provides functions for sequencing LED animations on a 3x4 LED matrix

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the 
  public domain worldwide. This software is distributed without any warranty.

  You should have received a copy of the CC0 Public Domain Dedication
  along with this software.
  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.  



#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial port(10,11);

#include <EasyVR.h>
EasyVR easyvr(port);



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

void VR_setup()
{
  T2S_starting_vr();
  // bridge mode?
  if (bridge.check())
  {
    T2S_bridge_on();
    cli();
    bridge.loop(0, 1, 10, 11);
  }
  // run normally
  port.begin(9600);
  

  if (!easyvr.detect())
  {
    T2S_hello();
    for (;;);
  }

  easyvr.setPinOutput(EasyVR::IO1, LOW);
  //T2S_hello();//started
  easyvr.setTimeout(5);
  easyvr.setLanguage(0);

  group = EasyVR::TRIGGER; //<-- start group (customize)
  T2S_yes();
}

void action();

void VR_loop()
{
  T2S_hello();
  easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)

  //Serial.print("Say a command in Group ");
  //Serial.println(group);
  easyvr.recognizeCommand(group);

  do
  {
    // can do some processing while waiting for a spoken command
  }
  while (!easyvr.hasFinished());
  
  easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off

  idx = easyvr.getWord();
  if (idx >= 0)
  {
    // built-in trigger (ROBOT)
    // group = GROUP_X; <-- jump to another group X
    return;
  }
  idx = easyvr.getCommand();
  if (idx >= 0)
  {
    // print debug message
    uint8_t train = 0;
    char name[32];
    //Serial.print("Command: ");
    //Serial.print(idx);
    if (easyvr.dumpCommand(group, idx, name, train))
    {
      //Serial.print(" = ");
      //Serial.println(name);
    }
    else
      //Serial.println();
    easyvr.playSound(0, EasyVR::VOL_FULL);
    // perform some action
    action();
  }
  else // errors or timeout
  {
    if (easyvr.isTimeout())
      T2S_error();
      //Serial.println("Timed out, try again...");
    int16_t err = easyvr.getError();
    if (err >= 0)
    {
      T2S_error();
      //Serial.print("Error ");
      //Serial.println(err, HEX);
    }
  }
}

void action()
{
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

*/
