// 2-dimensional array of row pin numbers (for two matrices):
const int row[8] = {//anodes
  8,9,10,11,12,13,A0,A1};

// 2-dimensional array of column pin numbers (for two matrices):
const int col[8] = {//cathodes
  2,3,4,5,6,7,A4,A5 };

  int x = 0;
  int y = 0;
  int pixels[8][8];  

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
      pixels[x][y] = LOW;
    }
  }
}

void loop() {
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
      delay (3);
      // turn the pixel off:
      /*if (thisPixel == LOW) {
        
        digitalWrite(col[thisCol], HIGH);
     
    } */
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }

x = random(0,7);
y = random(0,7);
pixels[x][y] = random(0,2);

Serial.print(x);
Serial.print(",");
Serial.print(y);
Serial.print("\t");
Serial.println(pixels[x][y]);


}}
