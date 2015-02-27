/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 9 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 Modified 17 June 2009
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */


int ledPin = 9;    // LED connected to digital pin 9
int rosso = 2;
int blu = 5;
int green = 12;
which = 1;

void setup()  { 
  // nothing happens in setup 


} 

void loop()  { 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);  
    which = random(1,3);
    if (which == 1){
      digitalWrite (rosso, LOW);
    }
    else if (which == 2){
      digitalWrite (blu, LOW);
    }
    else {
      digitalWrite (green, LOW);
    }
    // wait for 30 milliseconds to see the dimming effect    
    delay(30); 
    digitalWrite (rosso,HIGH);
    digitalWrite (blu,HIGH);
    digitalWrite (green,HIGH); 
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue); 
    which = random(1,3);
    if (which == 1){
      digitalWrite (rosso, LOW);
    }
    else if (which == 2){
      digitalWrite (blu, LOW);
    }
    else {
      digitalWrite (green, LOW);
    }
    // wait for 30 milliseconds to see the dimming effect    
    delay(30); 
    digitalWrite (rosso,HIGH);
    digitalWrite (blu,HIGH);
    digitalWrite (green,HIGH);     
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}



