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
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int pin = A0;  // Analog input pin that the potentiometer is attached to
int whichHeart = 0; //Selector for hearts
int previousHeart = 1; //Selector for hearts
int passHeart = 2;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int threshold = 30;
unsigned long talkTime = 0;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(pin,INPUT);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(pin);
  // map it to the range of the analog out:
  if (sensorValue > threshold) {
    outputValue = map(sensorValue, 0, 400, 0, 255);
    // change the analog out value:
    talkTime = millis();
  }
  else {
    outputValue = 0;
  }

  if ((millis() - talkTime) < 500) {

  }
  else if ((millis() - talkTime) < 1000) {
    passHeart = whichHeart;
    whichHeart = previousHeart;
    previousHeart = passHeart;
  }
  else if ((millis() - talkTime) < 2000) {
    passHeart = whichHeart;
    whichHeart = random(0,3);
    previousHeart = passHeart;
    while (previousHeart == whichHeart){
    previousHeart = random(0,3);
    }
  }
  
  for (int i = 0; i < 3; i++) {
    analogWrite(Heart[i], 0);
  }

  analogWrite(Heart[whichHeart], outputValue);


  // print the results to the serial monitor:
  Serial.print(whichHeart);
  Serial.print("  sensor = " );
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);
  

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}
