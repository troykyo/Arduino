//Randomly blink an 8x8 Matrix

unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time since the program started in Milliseconds
unsigned long blinkTime = 500;    // the  time since the program started in Milliseconds

// 2-dimensional array of row pin numbers:
const int row[19] = {
  8,15,19,5,13,7,1,1,1,1,1,1,1,1,1,1,1,1,1};

// 2-dimensional array of column pin numbers:
const int col[19] = {
  9,14,10,6,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// 2-dimensional array of pixels:
int pixels[8][8];           

// cursor position:
int x = 2;
int y = 3;

void setup() {
  
  // initialize the I/O pins as outputs

  // iterate over the pins:

  for (int thisPin = 0; thisPin < 20; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], HIGH);    
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 20; x++) {
    for (int y = 0; y < 20; y++) {
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
 if       pixels[1][1] == 0{
      pixels[1][1] = 1;
 }
 else{
   pixels == 0;
 }
}

void refreshScreen() {
  currentTime = millis();
  // iterate over the rows (anodes)
  for (int thisRow = 0; thisRow < 20; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 20; thisCol++) {
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

