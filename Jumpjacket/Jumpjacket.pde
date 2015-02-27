/* Based upon
 * _8x8 LED matrix
 * (c) 2009 BlushingBoy.net
 
 Jump Jacket Test 
 * Columns are Anode
 * Rows are Kathode
 
 
 */

#include "TimerOne.h"

byte rows[8] = {
  9, 14, 8, 12, 5, 7, 2, 1};
byte cols[8] = {
  13, 3, 4, 10, 6, 11, 15, 16};
byte pins[16] = {
  5, 4, 3, 2, 14, 15, 16, 17, 13, 12, 11, 10, 9, 8, 7, 6};
byte screen[8] = {
  0, 0, 0, 0, 0, 0, 0, 0};
volatile byte screenRow = 0;
volatile byte screenCol = 0;
byte x;
byte y;

void setup() {
  Timer1.initialize(100);
  Serial.begin (19200);
  for (int i = 2; i <= 17; i++)
    pinMode(i, OUTPUT);
  Timer1.attachInterrupt(doubleBuffer);
}

// interrupt routine
void doubleBuffer() {
  // reset the previous iteration
  digitalWrite(translatePin(rows[screenRow]), HIGH); // set previous off
  digitalWrite(translatePin(cols[screenCol]), LOW);  // set previous off
  // go to the next iteration...
  // go to the next screenCol, wrap if necessary
  screenCol++;
  if (screenCol >= 8) {
    screenCol = 0;
    // when screenCol wraps, go to the next screenRow, wrap if necessary
    screenRow++;
    if (screenRow >= 8) {
      screenRow = 0;
    }
  }
  // set this iteration
  if((screen[screenRow]>>screenCol)&B1 == B1) {
    digitalWrite(translatePin(rows[screenRow]), LOW);  // set this on
    digitalWrite(translatePin(cols[screenCol]), HIGH); // set this on
  } 
  else {
    digitalWrite(translatePin(rows[screenRow]), HIGH); // set this off
    digitalWrite(translatePin(cols[screenCol]), LOW);  // set this off
  }
}

byte translatePin(byte original) {
  return pins[original - 1];
}

void allOFF() {
  for (int i = 0; i < 8; i++)
    screen[i]=0;
}

void on(byte row, byte column) {
  screen[column] |= (B1<<(row)); 
}

void off(byte row, byte column) {
  screen[column] &= ~(B1<<(row)); 
}

// looping some LEDs routine
void loop() {
  allOFF();
  for (int j = 1; j <= 8; j++){
    for (int k = 1; k <= 8; k++){
      on (j,k);
      Serial.print(j);
      Serial.print(" ");
      Serial.println(k);
      delay(500);
      allOFF();      
    }   
  }
}


