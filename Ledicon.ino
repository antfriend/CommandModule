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

#define red_led 10
#define green_led 11
#define blue_led 9

void L_red_off()
{
  digitalWrite(red_led, LOW);
}

void L_setup()
{
  pinMode(red_led, OUTPUT);
  digitalWrite(red_led, LOW);
  pinMode(green_led, OUTPUT);
  digitalWrite(green_led, LOW);
  pinMode(blue_led, OUTPUT);
  digitalWrite(blue_led, LOW);
  
  digitalWrite(red_led, HIGH);
}

void L_LED_on()
{
  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, HIGH);
}

void L_LED_off()
{
  digitalWrite(blue_led, LOW);
  digitalWrite(green_led, HIGH);
  //T2S_flush();
}
