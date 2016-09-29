/*
  
  LED Icon Animation Module
                                                         
  Dan Ray antfriend@gmail.com
   
  This module provides functions for sequencing LED animations on a 3x4 LED matrix

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

void G_LED_on()
{
  digitalWrite(green_led, HIGH);
}

void G_LED_off()
{
  digitalWrite(green_led, LOW);
}

void X_LED_on()
{
  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, LOW);
  digitalWrite(red_led, HIGH);
}

void X_LED_off()
{
  digitalWrite(red_led, LOW);
  digitalWrite(blue_led, HIGH);
}

void L_LED_off()
{
  digitalWrite(blue_led, LOW);
  digitalWrite(green_led, HIGH);
  //T2S_flush();
}

