/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int cuore[] = { 
  -1,  2,3,4,5,6, 7,8,9,10,11, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int brightness = 0;
// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  for (int thisPin = 1; thisPin < 11; thisPin++)  {//output

    pinMode(cuore[thisPin], OUTPUT);
    analogWrite(cuore[thisPin], 255);    
    delay (300);
  }
  delay(1000);
} 

// the loop routine runs over and over again forever:
void loop() { 
  // set the brightness of pin 9:
  for (int thisPin = 1; thisPin < 11; thisPin++)  {//output
    analogWrite(cuore[thisPin], brightness);    
  }
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}


