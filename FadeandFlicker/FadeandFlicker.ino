/*
 Fade and Flicker
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 10 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 Modified 17 June 2009
 By Tom Igoe
  Modified 17 June 2009
 By Troy Nachtigall
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */


int ledPin = 10;    // LED connected to digital pin 9
int fadespeed = 5; // Variable for led fade speed
unsigned long lastTime = 0;
unsigned long thisTime = 0;
int intensita_Luce; // quanto brillante è ogni flicker di luce
int max_intensita_Luce = 255; // Brilantezza massimo per  ogni flicker di luce 
int min_intensita_Luce = 0; // // Brilantezza minimo per ogni flicker di luce
int flicker_Longevita; // Quanto tempo in millisecondi dura ogni flicker
int maxflicker_Longevita = 100; // Massimo tempo in millisecondi dura ogni flicker individuale
int minflicker_Longevita = 30; // Minimo tempo in millisecondi dura ogni flicker individuale


void setup()  { 
  // nothing happens in setup 
} 

void loop()  { 


  for(int counter = 1 ; counter <= 10; counter +=1) {
    fadespeed = random(5,12);
    // fade in from min to max in increments of 5 points:
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=fadespeed) { 
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);         
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    } 

    // fade out from max to min in increments of 5 points:
    for(int fadeValue = 255 ; fadeValue >= 20; fadeValue -=fadespeed) { 
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);         
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    } 

    delay(random(500,1500));
    lastTime = millis();
    thisTime =millis();
  }
  while ((abs(thisTime-lastTime))<20000) {
    intensita_Luce = random (min_intensita_Luce,max_intensita_Luce); // Intensita luce da random
    analogWrite(ledPin, intensita_Luce);   // accende lo LED  
    thisTime =millis();
    delay(flicker_Longevita);  // asspeta per la Longevita
  }
}




