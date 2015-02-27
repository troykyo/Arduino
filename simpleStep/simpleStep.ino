/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 9;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
unsigned int currentTime = 0; // what time is it right now.
unsigned int lastStepTime = 0;
int stepState = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);   
  pinMode(sensorPin, INPUT);   
  digitalWrite(sensorPin, HIGH);
  Serial.begin(9600);

}

void loop() {
  // read the value from the sensor:
  sensorValue = map(analogRead(sensorPin),0,1023,255,0);    
  // turn the ledPin on
  currentTime = millis();
 
 
  if (sensorValue > 10) {
    analogWrite(ledPin, sensorValue);
    if (stepState == 0) {
      lastStepTime = millis(); 
      stepState = 1;  
    }
    Serial.print(" ");
    Serial.print(sensorValue);
  }
  
  
  else{
    analogWrite(ledPin, 0);  
    if (stepState == 1) {
      Serial.println(" ");
      Serial.print("Step Time ");
      Serial.println(currentTime-lastStepTime);
      stepState = 0;
    }
  }

  delay(100);

}








