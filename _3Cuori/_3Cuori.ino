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
  if (counter % 10 == 0) {
    tenSoglia[tenCounter] = sensorValue;
    tenCounter++;
    minVolume++;//autotrim
    maxVolume--;//autotrim
    tenAverage = 0;
    hundredAverage = 0;
    thousandAverage = 0;
    for (int i = 0; i < 10; i++) {//average thresholds
      tenAverage = tenAverage + tenSoglia[i];
      hundredAverage = hundredAverage + hundredSoglia[i];
      thousandAverage = thousandAverage + thousandSoglia[i];
    }
    tenAverage = tenAverage / 10;
    hundredAverage = hundredAverage / 10;
    thousandAverage = thousandAverage / 10;
    Serial.print(" Dieci" );
    Serial.print(tenAverage);
    Serial.print(" Cento");
    Serial.print(hundredAverage);
    Serial.print(" Milla" );
    Serial.println(thousandAverage);
    if (tenCounter >= 10) {
      tenCounter = 0;
    }
  }
  if (counter % 100 == 0) {
    hundredSoglia[hundredCounter] = sensorValue;
    hundredCounter++;
    if (hundredCounter >= 10) {
      hundredCounter = 0;
    }
  }
  if (counter % 1000 == 0) {
    thousandSoglia[thousandCounter] = sensorValue;
    thousandCounter++;
    if (thousandCounter >= 10) {
      thousandCounter = 0;
    }
  }
  if ((counter > 60 * 60 * 1000) || ((counter > 18000) && (counter / soundCounter < 2))) { //reset the threshold every hour or if the LEDs have been on more than half time time in the last three minutes
    counter = 1;
    soundCounter = 0;
    maxVolume = 0;
    minVolume = 1000;
  }

  sensorValue = 0;
  for (int j = 0; j < 50; j++) {//Listen 10 Times and average
    sensorValue = sensorValue + analogRead(analogInPin);// read the analog in value
  }
  sensorValue = sensorValue / 50;

  if (sensorValue > maxVolume) {//Max
    maxVolume = sensorValue;
  }
  if (sensorValue < minVolume) {//Min Volume
    minVolume = sensorValue;
  }
  if (counter == 10000) {// pass the hundred average to the thousands
    for (int i = 0; i < 10; i++) {//average thresholds
      thousandSoglia[i] = hundredAverage;
    }
  }
  if (counter > 10000) {
    threshold = thousandAverage;
    Serial.print("1000 Soglia ");
    Serial.println(threshold);
  }
  if (counter > 1000) {
    threshold = hundredAverage;
    Serial.print("100 Soglia ");
    Serial.println(threshold);
  }
  else {
    threshold = tenAverage;
    Serial.print("10 Soglia ");
    Serial.println(threshold);
  }


  /* if ((threshold < minVolume) || (threshold > maxVolume))  {//sanity check
     threshold = (maxVolume - minVolume) * .2; //set the base threshold
     Serial.print("Soglia Reset ");
  }*/

  for (int i = 0; i < 3; i++) {//reset all hearts to 0
    analogWrite(Heart[i], 0);
  }

  if (sensorValue > (threshold * sensibilita))  { //volume is 10% louder than the threshold
    talkTime = millis();
    soundCounter++;
    sensorValue = constrain(sensorValue, minVolume, maxVolume);
    outputValue = map(sensorValue, minVolume, maxVolume, 50, 255);// change the analog out value:
    analogWrite(Heart[whichHeart], outputValue);
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
