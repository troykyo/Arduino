/*
  Vittorio Corsini,  3 Cuori

Questo Sketch ascolta per perosne che parlano e fa uno di tre cuori lampagiare
con la volume di voce della persone

 Il circuito:
* Collega un microphono GND a GND, 5v a 5v, e OUT a A0
 * LED colegate a pwm pin 9,10,11 to ground

Created Jan 2015 by @troykyo Troy Nachtigall for Vittorio Corsini

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int Heart[] = {11, 10, 9}; // Analog output pin that the LED is attached to

int whichHeart = 0; //Selector for hearts
int previousHeart = 1; //Selector for hearts
int passHeart = 2;
unsigned long sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
unsigned long threshold = 30;
unsigned long talkTime = 0;
unsigned long offTime = 0; //The Time we started talking. Probably needs debounced
unsigned long counter = 0;
unsigned long soundCounter = 0;//How much is the sound on?
int suono = 0;
unsigned long maxVolume = 0;
unsigned long minVolume = 1000;
unsigned long tenSoglia[] = {70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 0};
unsigned long hundredSoglia[] = {70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 0};
unsigned long thousandSoglia[] = {70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 0};
unsigned long tenCounter = 0;
unsigned long hundredCounter = 0;
unsigned long thousandCounter = 0;
unsigned long tenAverage = 0;
unsigned long hundredAverage = 0;
unsigned long thousandAverage = 0;
int sensibilita = 1.2; // Da 1.1 a 1.3


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  whichHeart = random(0, 3);
  analogWrite(Heart[0], 255);
  delay(500);
  analogWrite(Heart[1], 255);
  delay (500);
  analogWrite(Heart[2], 255);
  delay (500);

  for (int j = 0; j < 100; j++) {//reset all hearts to 0
    sensorValue = sensorValue + analogRead(analogInPin);// read the analog in value

    Serial.print(sensorValue);
    Serial.print(" ");
  }
  sensorValue = sensorValue / 100;
  Serial.println(sensorValue);

  if (sensorValue > maxVolume) {//Max
    maxVolume = sensorValue;
  }
  if (sensorValue < minVolume) {//Min Volume
    minVolume = sensorValue;
  }

  threshold = (maxVolume - minVolume) * .2 + minVolume; //set the base threshold
  for (int i = 0; i <= 10; i++) {//average thresholds
    tenSoglia[i] = threshold;
    hundredSoglia[i] = threshold;
    thousandSoglia[i] = threshold;
  }
  analogWrite(Heart[1], 0);
  analogWrite(Heart[2], 0);
  analogWrite(Heart[3], 0);
  maxVolume = 0;
  minVolume = 1000;
}

void loop() {
  counter++;//nubmer of loops for the running average
  for (int j = 0; j < 10; j++) {//Listen 10 Times and average
    sensorValue = sensorValue + analogRead(analogInPin);// read the analog in value
  }
  sensorValue = sensorValue / 10;
  if (counter % 10 == 0) {
    tenSoglia[tenCounter] = sensorValue;
    tenCounter++;
    if (tenCounter >= 10) {
      tenCounter = 0;
    }
  }
  maxVolume = 0;
  minVolume = 1000;
  for (int i = 0; i < 10; i++) {//average thresholds
    tenAverage = tenAverage + tenSoglia[i];
    if (tenSoglia[i] > maxVolume) {//Max
      maxVolume = tenSoglia[i];
    }
    if (tenSoglia[i] < minVolume) {//Min Volume
      minVolume = tenSoglia[i];
    }
  }
    for (int i = 0; i < 3; i++) {//reset all hearts to 0
    analogWrite(Heart[i], 0);
  }
  if ((sensorValue == minVolume) || (sensorValue == maxVolume) ) { //volume is 10% louder than the threshold
    talkTime = millis();
    soundCounter++;
    digitalWrite(Heart[whichHeart], HIGH);
    delay (50);
  }
  if ((millis() - talkTime) < 400) {
    //Stay on the same heart
  }
  else if ((millis() - talkTime) < 800) {
    passHeart = whichHeart;
    whichHeart = previousHeart;
    previousHeart = passHeart;
  }
  else if ((millis() - talkTime) < 1600) {
    passHeart = whichHeart;
    whichHeart = random(0, 3);
    previousHeart = passHeart;
    while (previousHeart == whichHeart) {
      whichHeart = random(0, 3);
    }
  }

  // print the results to the serial monitor:

  Serial.print(" Cuore " );
  Serial.print(whichHeart);
  Serial.print(" Sensor Value " );
  Serial.print(sensorValue);
  Serial.print(" Threshold ");
  Serial.print(threshold);
  Serial.print(" Min " );
  Serial.print(minVolume);
  Serial.print(" Max ");
  Serial.println(maxVolume);
}
