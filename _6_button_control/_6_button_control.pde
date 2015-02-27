/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 Modified 4 Sep 2010
 by Tom Igoe
 
 This example code is in the public domain.
 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin[] = {
  A0,A1,A2,A3,A4,A5}; 

const int ledPin = 13; // Analog output pin that the LED is attached to

int sensorValue[] = {
  1,1,1,1,1,1};        // value read from the pot


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
for (int thisPin = 0; thisPin < 6; thisPin++) {
  sensorValue[thisPin] = analogRead(analogInPin[thisPin]);            
Serial.print(thisPin);   
Serial.print(" = " );
Serial.print(sensorValue[thisPin]);   
Serial.print(", " );
  delay(10); 
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
                    }
Serial.println();                    
}
