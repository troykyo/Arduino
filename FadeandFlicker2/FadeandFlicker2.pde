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
 
 */h
int ledPin = 10;    // LED connected to digital pin 9
int fadespeed = 5; // Variable for led fade speed
int fadeValue=0;
unsigned long lastTime = 0;
unsigned long thisTime = 0;
int intensita_Luce; // quanto brillante è ogni flicker di luce
int max_intensita_Luce = 255; // Brilantezza massimo per  ogni flicker di luce 
int min_intensita_Luce = 127; // // Brilantezza minimo per ogni flicker di luce
int flicker_Longevita; // Quanto tempo in millisecondi dura ogni flicker
int maxflicker_Longevita =70; // Massimo tempo in millisecondi dura ogni flicker individuale
int minflicker_Longevita = 50; // Minimo tempo in millisecondi dura ogni flicker individuale
int flicker=0; // variable for flickering
int delaySpeed = 30;

void setup()  { 
  Serial.begin(9600);
  HalfBreath();
} 

void loop()  { 


  FullBreath();
  Flick();

}
void FullBreath() {
  delaySpeed = random (25,40);
  Serial.println (delaySpeed);
  // for(int counter = 1 ; counter <= 10; counter +=1) {
  fadespeed = random(5,12);
  // fade in from min to max in increments of 5 points:
  for(fadeValue = 0 ; fadeValue <= 255; fadeValue +=fadespeed) { 
    // sets the value (range from 0 to 255):
    fadespeed = map(fadeValue, 0,255,1,10);
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    Serial.print(fadespeed);
    delay(delaySpeed);                            
  } 

  delay(random(500,1500));
  // fade out from max to min in increments of 5 points:
  for( fadeValue = 255 ; fadeValue >= 0; fadeValue -=fadespeed) { 
    // sets the value (range from 0 to 255):
    fadespeed = map(fadeValue, 0,255,1,10);
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    Serial.print(fadespeed);
    delay(delaySpeed);                            
  } 
  Serial.println();
}
void HalfBreath() {
  delaySpeed = random (25,40);
  Serial.println (delaySpeed);
  // for(int counter = 1 ; counter <= 10; counter +=1) {
  fadespeed = random(5,12);
  // fade in from min to max in increments of 5 points:
  for(fadeValue = 0 ; fadeValue <= 175; fadeValue +=fadespeed) { 
    // sets the value (range from 0 to 255):
    fadespeed = map(fadeValue, 0,175,1,10);
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    Serial.print(fadespeed);
    delay(delaySpeed);                            
  } 

  delay(random(500,1500));
  // fade out from max to min in increments of 5 points:
  for( fadeValue = 175 ; fadeValue >= 0; fadeValue -=fadespeed) { 
    // sets the value (range from 0 to 255):
    fadespeed = map(fadeValue, 0,175,1,10);
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    Serial.print(fadespeed);
    delay(delaySpeed);                            
  } 
  Serial.println();
}
void resetFade(){
  while (fadeValue > 1){
    fadeValue--;
    //if (fadespeed>1){
    //fadespeed-- ; 
    //}
    analogWrite(ledPin, fadeValue);         
    delay (50);
    Serial.print(".");
  }
}
void Flick()
{
  flicker = random(1,10);
  Serial.println(flicker, DEC);
  if (flicker==7){
    //delay(random(500,1500));
    lastTime = millis();
    thisTime =millis();
    while ((abs(thisTime-lastTime))<(random(5000,10000))) {
      intensita_Luce = random (min_intensita_Luce,max_intensita_Luce); // Intensita luce da random
      analogWrite(ledPin, intensita_Luce);   // accende lo LED  
      thisTime =millis();
      flicker_Longevita = random(minflicker_Longevita,maxflicker_Longevita);
      delay(flicker_Longevita);  // asspeta per la Longevita
    }
  }
  else if ((flicker==3) || (flicker = 9)){
    HalfBreath();
  }
}











