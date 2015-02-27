/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;
unsigned int sendTime[7] = {
  500,500,1000,2000,1000,502,500};//array to send 
int sendTimeLength = 7; //number of chrachters in the send Time array.  Remember to start counting with 0.

void setup()
{
  Serial.begin(9600);
}

void loop() {
    for (int i = 0; i < 3; i++) {
      digitalWrite(13,LOW);

     irsend.sendRaw(sendTime,sendTimeLength, 36); // 0 counts
      digitalWrite(13,HIGH);
      delay(500);
    }
  delay (1000);
}
