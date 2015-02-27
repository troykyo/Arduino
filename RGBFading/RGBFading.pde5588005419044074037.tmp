// Fading LED 
// by BARRAGAN <http://people.interaction-ivrea.it/h.barragan> 

int value = 0;                            // variable to keep the actual value 
int ledpinR = 9;                           // light connected to digital pin 9
int ledpinG = 10;                           // light connected to digital pin 10 
int ledpinB = 11;                           // light connected to digital pin 11

void setup() 
{ 
  // nothing for setup  ¬,waszx 
} 
 
void loop() 
{ 
  for(value = 0 ; value <= 255; value+=5) // fade in (from min to max) 
  { 
    analogWrite(ledpinR, value);           // sets the value (range from 0 to 255) 
    analogWrite(ledpinG, value);           // sets the value (range from 0 to 255)
    analogWrite(ledpinB, value);           // sets the value (range from 0 to 255)  
    delay(30);                            // waits for 30 milli seconds to see the dimming effect 
  } 
  for(value = 255; value >=0; value-=5)   // fade out (from max to min) 
  { 
    analogWrite(ledpinR, value);
    analogWrite(ledpinG, value); 
    analogWrite(ledpinB, value);
    delay(30); 
  }  
} 
