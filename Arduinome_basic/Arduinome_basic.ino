//Randomly blink an 8x8 Matrix

unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time since the program started in Milliseconds
unsigned long blinkTime = 400;    // the  time since the program started in Milliseconds

// 2-dimensional array of row pin numbers:
const int row[8] = {
  2,7,19,5,13,18};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  6,11,10,0,0,0};

// 2-dimensional array of pixels:
int pixels[8][8];           

// cursor position:
int x = 2;
int y = 3;

void setup() {
  
  // initialize the I/O pins as outputs

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
      pixels[x][y] = 1;
    }
  }
}

void loop() {
  setMatrix();
  while ((abs(currentTime-startTime))<blinkTime){ 
    // draw the screen:
    refreshScreen();
  }
}

void setMatrix() {
  // turn off the last position:
  startTime = millis();
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 6; y++) {
      pixels[x][y] = random(0,1);
    }
  }
}

void refreshScreen() {
  currentTime = millis();
  // iterate over the rows (anodes)
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

