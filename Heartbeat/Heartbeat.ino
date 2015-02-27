/*
Heartbeat: Created by Troy Nachtigall for Palazzo Strozzi
 
 */

int BPM = 59;
int BPMdelay = 0;
int ledPin = 0;    // LED connected to digital pin 0
int delayBat = 1;
int BeatSpeed = 15; //how fast the beat happens


void setup()  { 
 pinMode(ledPin,OUTPUT);
BPMdelay = 60/BPM *1000;
} 

void loop()  { 
  // fade in from min to max in increments of 5 points:

 for(int fadeValue = 0 ; fadeValue <= 80; fadeValue +=BeatSpeed) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(delayBat);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 80 ; fadeValue >= 0; fadeValue -=BeatSpeed) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(delayBat);                            
  } 
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=BeatSpeed) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(delayBat);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=BeatSpeed) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(delayBat);                            
  } 
 

  
delay(BPMdelay);

}



