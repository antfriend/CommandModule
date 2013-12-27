/*
  
  LED Icon Animation Module
                                                         
  Dan Ray antfriend@gmail.com
  12/15/2013
  
  This module provides functions for sequencing LED animations on a 3x4 LED matrix

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the 
  public domain worldwide. This software is distributed without any warranty.

  You should have received a copy of the CC0 Public Domain Dedication
  along with this software.
  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.  
*/
#define ledPin 13

void L_setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void L_LED_on()
{
  digitalWrite(ledPin, HIGH);
}

void L_LED_off()
{
  digitalWrite(ledPin, LOW);
  //T2S_flush();
}
