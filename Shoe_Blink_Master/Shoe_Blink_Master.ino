//Button Variables
const int numReadings = 10;
int buttonTime1[numReadings];      // the readings from the analog input
int buttonTime2[numReadings];      // the readings from the analog input
const int numSteps = 10;
unsigned long stepTime1[numSteps];
unsigned long stepTime2[numSteps];
int index = 0;                  // the index of the current reading
int total1 = 0;                  // the running total
int total2 = 0;                  // the running total
int average1 = 0;                // the average
int average2 = 0;                // the average
int mode = 0;
int lastMode = 0;
int blinkblink = 0;
const int butt1 = 14;
const int butt2 = 15;
int randomPixel=0;
int RGB[6];
int colorTime = 0;
int ledR = 5;
int ledG = 6;
int ledB = 9;



unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time since the program started in Milliseconds
unsigned long blinkTime = 1000;    // the  time since the program started in Milliseconds

// 2-dimensional array of row pin numbers:
const int row[6] = {

  9,8,7,6,5,4};
// 2-dimensional array of column pin numbers:
const int col[6] = {
  10,11,12,2,2,2};

// 2-dimensional array of pixels:
int pixels[6][6];           

// cursor position:
int x = 2;
int y = 3;

void setup() {
  digitalWrite(13, HIGH); 

  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
  pinMode(butt1, OUTPUT); //declare all the buttons as inputs
  digitalWrite(butt1, HIGH); // set the inernal pull up resistor.
  pinMode(butt2, OUTPUT); //declare all the buttons as inputs
  digitalWrite(butt2, HIGH); // set the inernal pull up resistor.
  // initialize the I/O pins as outputs

  // iterate over the pins:

  for (int thisPin = 0; thisPin < 6; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT); 
    RGB[thisPin] = 0;

    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], HIGH);    
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 6; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {
  setMatrix();
  //for (int k = 0; k < 100; k++) {
  // draw the screen:
  refreshScreen();
  footsteps();
  //Serial.print(k);
  // }
  //Serial.println();
}

void colorSet(){
  if ((RGB[1]==RGB[4]) && (RGB[2]==RGB[5]) && (RGB[3]==RGB[6])){//reset the color because all the LEDs are the right color
    for (int x = 1; x < 4; x++) {
      RGB[x] = random(0,255);
    }
  }

  for (int x = 1; x < 4; x++) {
    if (RGB[x] > RGB[x+3]){
      RGB[x]--;
    }
    else if (RGB[x] < RGB[x+3]){
      RGB[x]++;
    }
  }
  analogWrite (ledR, RGB[1]);
  analogWrite (ledG, RGB[2]);
  analogWrite (ledB, RGB[3]);
}

void setMatrix() {
  Serial.println(mode);
  // turn off the last position:
  //if (mode <= 0) {//random blink pattern
  if (lastMode != 1){//mode test for timing
    startTime = millis();
    lastMode = 1;
    blinkTime = 1000;
  }
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 6; y++) {
      randomPixel = random(0,100);
      if (randomPixel > 40){
        pixels[x][y] = LOW;
      }
      else {
        pixels[x][y] = HIGH;
      }

      Serial.print(pixels[x][y]);
    }
    Serial.println(".");
  }
}
/*
  else if (mode >= 0){//Scrolling walk mode.
 if (lastMode != 2){//mode test for timing
 startTime = millis();
 lastMode = 2;
 blinkTime = 200;
 blinkblink=0;
 }
 blinkblink++;
 blinkblink = blinkblink%6;
 for (int x = 0; x < 3; x++) {
 for (int y = 0; y < 6; y++) {
 if ((x - blinkblink<=1) && (y - blinkblink<=1)) {  // are we less than one step away from blinkblink?
 pixels[x][y] = HIGH;
 }
 else{
 pixels[x][y] = LOW;
 }
 }
 }
 }
 else if (mode == 0){//1 second on/off
 if (lastMode != 3){//mode test for timing
 startTime = millis();
 lastMode = 3;
 blinkTime = 1000;
 }
 if (blinkblink > 0) {
 blinkblink = 0; 
 for (int x = 0; x < 3; x++) {
 for (int y = 0; y < 6; y++) {
 pixels[x][y] = HIGH;
 }
 }
 }
 else{
 blinkblink = 1; 
 for (int x = 0; x < 3; x++) {
 for (int y = 0; y < 6; y++) {
 pixels[x][y] = LOW;
 }
 }
 }   
 }
 }*/

void refreshScreen() {
  currentTime = millis();
  // iterate over the rows (anodes)
  for (int thisRow = 0; thisRow < 6; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 3; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      if (thisPixel==HIGH){
        Serial.print("o");
      }
      if (thisPixel==LOW){
        Serial.print("x");
      }
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
    Serial.println("-");
    step();
  }
}

void step(){//measures the timing of each step, checks to ensure a step occured.
  index++;
  if (index > numSteps){ 
    index=1;
    stepTime1[0] = pulseIn(butt1,HIGH,60000);
    stepTime2[0] = pulseIn(butt2,HIGH,60000);
  }  
  stepTime1[index] = pulseIn(butt1,HIGH,60000);
  stepTime2[index] = pulseIn(butt2,HIGH,60000);
  if (((stepTime1[index]-stepTime1[index-1])==0)&&((stepTime2[index]-stepTime2[index-1])==0)){
    index--;
    mode--;
  }
  if ((stepTime1[index]>stepTime1[index-1])&&(stepTime2[index]>stepTime2[index-1])){
    index--;
    mode--;
    stepTime1[index-1]=stepTime1[index];
    stepTime2[index-1]=stepTime2[index];
  }
}

void footsteps(){
  currentTime = millis();
  index++;
  total1 = total1 + abs(stepTime1[index]-stepTime1[index-1]);
  total2 = total2 + abs(stepTime2[index]-stepTime2[index-1]);
  if (abs(stepTime1[index]-stepTime2[index])<30){
    mode--;
  }
  else if (stepTime1[index] > stepTime2[index]){
    mode+2;
  }
  else if (stepTime2[index] > stepTime1[index]){
    mode++;
  }
}






/*
 This code is based upon:
 Row-Column Scanning an 8x8 LED matrix with X-Y input
 
 This example controls an 8x8 LED matrix using two analog inputs
 
 created 27 May 2009
 modified 30 Aug 2011
 by Tom Igoe
 
 This example works for the Lumex  LDM-24488NI Matrix. See 
 http://sigma.octopart.com/140413/datasheet/Lumex-LDM-24488NI.pdf
 for the pin connections
 
 For other LED cathode column matrixes, you should only need to change 
 the pin numbers in the row[] and column[] arrays
 
 rows are the anodes
 cols are the cathodes
 ---------
 
 Pin numbers:
 Matrix:
 * Digital pins 2 through 13,
 * analog pins 2 through 5 used as digital 16 through 19
 Potentiometers:
 * center pins are attached to analog pins 0 and 1, respectively
 * side pins attached to +5V and ground, respectively.
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/RowColumnScanning
 
 see also http://www.tigoe.net/pcomp/code/category/arduinowiring/514 for more
 */
























