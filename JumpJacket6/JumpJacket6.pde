/*---------------
 Jump Jacket
 Troy Nachtigall
 www.troykyo.com
 ---------------*/

#include <Wire.h>
#include "nunchuck_funcs.h"

byte xjoy,yjoy,accx,accy,accz,zbut,cbut; //wimote variables
byte rowmap,rowmin,rowmax,colmap,colmin,colmax; //control variables 
int flash = 10; //controls the blink speed
int x = 5;
int y = 5;
int thisRow = 0;
int thisCol = 0;
//unsigned long time=0;

const int col[8] = { // 2-dimensional array of row pin numbers:
  6,11,10,3,14,4,8,9 };
const int row[5] = { // 2-dimensional array of column pin numbers
  2,7,12,5,13 };
int pixels[8][8]; // 2-dimensional array of pixels:         


void setup() {
  Serial.begin(9600);
  nunchuck_setpowerpins();//analog 2 and 3 become power
  nunchuck_init(); // send the initilization handshake
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are on:
    digitalWrite(col[thisPin], LOW);    
  }
  for (int thisPin = 0; thisPin < 5; thisPin++) {
    pinMode(row[thisPin], OUTPUT);  
  }
  // initialize the pixel matrix:
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = LOW;
    }
  }
  Serial.println("GO!");
}

void loop() {
  // read input:
  readSensors();

  // draw the screen:
  refreshScreen();

}

void readSensors() {
  nunchuck_get_data(); //reads nunchuck
  accx  = nunchuck_accelx(); // ranges from approx 70 - 182
  accy  = nunchuck_accely(); // ranges from approx 80 - 200
  accz  = nunchuck_accelz(); // ranges from approx 78 - 200
  zbut = nunchuck_zbutton();
  cbut = nunchuck_cbutton(); 
  xjoy = nunchuck_joyx();
  yjoy = nunchuck_joyy();

  if (zbut == 1)//flash slower
    flash=flash+3;
  if (cbut == 1)//flash faster 
    flash=flash-3;
  if (flash<1)
    flash = 1;

  Serial.print("accx: "); 
  Serial.print((byte)accx,DEC);
  Serial.print("\taccy: "); 
  Serial.print((byte)accy,DEC);
  Serial.print("\taccz: "); 
  Serial.print((byte)accz,DEC);
  Serial.print("\tzbut: "); 
  Serial.print((byte)zbut,DEC);
  Serial.print("\tcbut: "); 
  Serial.print((byte)cbut,DEC);
  Serial.print("\txjoy: "); 
  Serial.print((byte)xjoy,DEC);
  Serial.print("\tyjoy: "); 
  Serial.print((byte)yjoy,DEC);

  // turn off the last position:
  //pixels[x][y] = HIGH;
  // read the sensors for X and Y values:
  // time = millis();
  // x = (time/1000)%8;
  // y = (time/1000)%8;
  // set the new pixel position low so that the LED will turn on
  // in the next screen refresh:
  //pixels[x][y] = LOW;
  //Serial.print (x);
  //Serial.print (" ");
  //Serial.println (y);*/
}

void refreshScreen() {
  rowmap = map(accy,80,200,0,5); // acelerometer mapping
  colmap = map(accx,70,190,-4,4);
  rowmin = 0;
  if (rowmap > 0 && rowmap < 3)  //if tilted forward set min 
    rowmin = rowmap;
  rowmax = 5;
  if (rowmap > 2 && rowmap < 6)//if tilted forward set max
    rowmax = rowmap;
  colmin = 0;
  if (colmap > -5 && colmap < 0)//if tilted left set min
    colmin = colmin + (abs(colmap));
  colmax = 5;
  if (colmap > 0 && colmap < 5)//if tilted forward set max
    colmin = colmin - (abs(colmap));  
  Serial.print("\trowmap: "); 
  Serial.print((byte)rowmap,DEC);
  Serial.print("\tcolmap: "); 
  Serial.print((byte)colmap,DEC);
  Serial.print("\tRowMin: "); 
  Serial.print((byte)rowmin,DEC);
   Serial.print("\tRowMax: "); 
  Serial.print((byte)rowmax,DEC);
  Serial.print("\tColMin: "); 
  Serial.print((byte)colmin,DEC);
   Serial.print("\tColMax: "); 
  Serial.print((byte)colmax,DEC);
  
  if (yjoy > 200 || accy > 150 ) // if joy is presed forward scroll down
    scrollDown();
  else 
    scrollUp();
}

void scrollDown(){
  // iterate over the rows (anodes):
  for (thisRow = rowmin; thisRow < rowmax; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], LOW);
    // iterate over the cols (cathodes):
    if (xjoy < 60)
      scrollLeft();
    else
      scrollRight();
  } 
}

void scrollUp(){
  // iterate over the rows (anodes):
  for (thisRow = rowmax; thisRow >= rowmin; thisRow--) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], LOW);
    // iterate over the cols (cathodes):
    if (xjoy < 60)
      scrollLeft();
    else
      scrollRight();
  } 
}  

void scrollLeft() {  
  for (thisCol = colmin; thisCol < colmax; thisCol++) {
    // get the state of the current pixel;
    int thisPixel = pixels[thisRow][thisCol];
    // when the row is HIGH and the col is LOW,
    // the LED where they meet turns on:
    // Serial.println (thisPixel);
    digitalWrite(col[thisCol], thisPixel);
    // turn the pixel off:
    //if (thisPixel == LOW) {
    //digitalWrite(col[thisCol], HIGH);
    //}
    delay(flash);
  }
  // take the row pin low to turn off the whole row:
  digitalWrite(row[thisRow], HIGH);
}

void scrollRight (){  
  for (thisCol = colmax; thisCol >= colmin; thisCol--) {
    // get the state of the current pixel;
    int thisPixel = pixels[thisRow][thisCol];
    // when the row is HIGH and the col is LOW,
    // the LED where they meet turns on:
    // Serial.println (thisPixel);
    digitalWrite(col[thisCol], thisPixel);
    // turn the pixel off:
    //if (thisPixel == LOW) {
    //digitalWrite(col[thisCol], HIGH);
    //}
    delay(flash);
  }
  // take the row pin low to turn off the whole row:
  digitalWrite(row[thisRow], HIGH);
}

/*

 -  This code is based upon the following code.  Thanks to all who came before.-
 
 * Nunchuck functions  -- Talk to a Wii Nunchuck
 *
 * This library is from the Bionic Arduino course : 
 *                          http://todbot.com/blog/bionicarduino/
 *
 * 2007 Tod E. Kurt, http://todbot.com/blog/
 *
 * The Wii Nunchuck reading code originally from Windmeadow Labs
 *   http://www.windmeadow.com/node/42
 
 
 Row-Column Scanning an 8x8 LED matrix with X-Y input
 
 This example controls an 8x8 LED matrix using two analog inputs
 
 created 27 May 2009
 modified 4 Sep 2010
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
 
 This code is in the public domain.
 See that base by Tom Igoe at 
 http://www.arduino.cc/en/Tutorial/RowColumnScanning
 
 */












