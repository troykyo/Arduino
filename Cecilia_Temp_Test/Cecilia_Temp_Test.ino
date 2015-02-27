/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 9;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot


// the setup routine runs once when you press reset:
void setup() {   
  Serial.begin(9600); 
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  
  pinMode(analogInPin, INPUT);     
  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  sensorValue = analogRead(analogInPin);            
  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensorValue); 
  int temperatureCel = (((sensorValue-502)*15)/97)+20;  
  Serial.print(" Celcius = " );                       
  Serial.println(temperatureCel); 
  delay(10);               // wait for a second
}

