const int row[6] = {
 
10,11,12,2,2,2};
// 2-dimensional array of column pin numbers:
const int col[6] = {
   9,8,7,6,5,4}; 

// 2-dimensional array of pixels:
int pixels[6][6];           

// cursor position:
int x = 5;
int y = 5;
int j=0;
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
      pixels[x][y] = LOW;
    }
  }

}

void loop() {
  j++;
  if (j==1000){
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        pixels[x][y] = HIGH;
      }
    }
    
    delay (1000);
    for (int x = 0; x < 6; x++) {
      for (int y = 0; y < 6; y++) {
        pixels[x][y] = random(0,1);
      }
    }
    j=0;
  }
  // draw the screen:
  refreshScreen();
}



void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 6; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 6; thisCol++) {
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


