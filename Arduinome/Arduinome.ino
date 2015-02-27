/*
  8x8 LED matrix with accelerometer
 for Arduino 
 
 This example controls an 8x8 LED matrix using two inputs
 from an accelerometer.
 
 created 27 May 2009
 by Tom Igoe
 
 The matrix used is labeled  HS-788AS.  It was bought surplus.
 It is laid out as follows 
 (warning: yours might have different pin configurations):
 
 rows are the anodes
 cols are the cathodes
 
 label HS-788AS is on the left side of the chip
 _________
 col 4  ----|         |---- row 1
 col 2  ----|         |---- row 2
 row 7  ----|         |---- col 7
 row 6  ----|         |---- row 8
 col 1  ----|         |---- col 5
 row 4  ----|         |---- row 3
 col 3  ----|         |---- row 5
 col 6  ----|         |---- col 8
 ---------
 
 Pin numbers:
 Matrix:
 2 through 13, analog 2 througnh used as digital 16 through 19
 Accelerometer: 
 X and Y axes attached to analog in 0 and 1
 
 */

const int debounceMin = 50;

// 2-dimensional array of row pin numbers (for two matrices):
const int row[8] = {
  2,3,4,5,6,7,A4,A5 };

// 2-dimensional array of column pin numbers (for two matrices):
const int col[8] = {
  8,9,10,11,12,13,A0,A1  };

// 2-dimensional array of pixels:
int pixels[8][8];  
int pixelTime[8][8];
int pixelStatus[8][8]; 
int previousStatus[8][8]; 

void setup() {
  Serial.begin(9600);
  // initialize the I/O pins as outputs:

  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], HIGH);    
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {
  // read input:
  readSensors();
  // draw the screen:
  for (int go = 0; go < 8; go++) {
    refreshScreen();
  }
}

void readSensors() {
  DDRD = B00000000;  // sets Arduino pins 1 to 7 as outputs, pin 0 as input
  DDRB = B000000;  // sets Arduino pins 8 to 13 as outputs, pin 0 as input
  DDRC = B000000;  // sets Arduino pins 8 to 13 as outputs, pin 0 as input
  // turn off the last position:
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      digitalWrite(col[thisRow], HIGH);  //turnon the pullup resistor
      pixelStatus[thisRow][thisCol] = digitalRead(col[thisRow]);
      if (pixelStatus[thisRow][thisCol] == HIGH){
        if (previousState[thisRow][thisCol] == 0){
          previousState[thisRow][thisCol] = 1;
          pixelTime [thisRow][thisCol] = millis();
        }
        if (abs(millis() - pixelTime [thisRow][thisCol]) > debounceMin){
        pixels[thisRow][thisCol] = pixelStatus[thisRow][thisCol];
        }
      }
      else if (pixelStatus[thisRow][thisCol] == LOW){
        previousState[thisRow][thisCol] = 0;
        
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}



void refreshScreen() {
  DDRD = B11111110;  // sets Arduino pins 1 to 7 as outputs, pin 0 as input
  DDRB = B111111;  // sets Arduino pins 8 to 13 as outputs, pin 0 as input
  DDRC = B111111;  // sets Arduino pins 8 to 13 as outputs, pin 0 as input

  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }

}




