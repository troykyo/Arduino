/*
 * Jump Jacket Code
 * 
 * Columns are Anode
 * Rows are Kathode
 */

#include "TimerOne.h"
#include <Wire.h>
#include <string.h>

#undef int
#include <stdio.h>

uint8_t outbuf[6];		// array to store arduino output
int cnt = 0;
byte rows[8] = {9, 14, 8, 12, 1, 7, 2, 5};
byte cols[8] = {13, 3, 4, 10, 6, 11, 15, 16};
byte pins[16] = {5, 4, 3, 2, 14, 15, 16, 17, 13, 12, 11, 10, 9, 8, 7, 6};
byte screen[8] = {0, 0, 0, 0, 0, 0, 0, 0};
volatile byte screenRow = 0;
volatile byte screenCol = 0;

void setup() {
  Serial.begin (19200);
  Serial.print ("Finished setup\n");
  Wire.begin ();		// join i2c bus with address 0x52
  nunchuck_init (); // send the initilization handshake
  Timer1.initialize(100);
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
  } else {
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
    screen[column-1] |= (B1<<(row-1)); 
}

void off(byte row, byte column) {
    screen[column-1] &= ~(B1<<(row-1)); 
}
void
nunchuck_init ()
{
  Wire.beginTransmission (0x52);	// transmit to device 0x52
  Wire.send (0x40);		// sends memory address
  Wire.send (0x00);		// sends sent a zero.  
  Wire.endTransmission ();	// stop transmitting
}

void
send_zero ()
{
  Wire.beginTransmission (0x52);	// transmit to device 0x52
  Wire.send (0x00);		// sends one byte
  Wire.endTransmission ();	// stop transmitting
}


void loop() {
  Wire.requestFrom (0x52, 6);	// request data from nunchuck
  while (Wire.available ())
    {
      outbuf[cnt] = nunchuk_decode_byte (Wire.receive ());	// receive byte as an integer
      //digitalWrite (ledPin, HIGH);	// sets the LED on
      cnt++;
    }

  // If we recieved the 6 bytes, then go print them
  if (cnt >= 5)
    {
      print ();
    }

  cnt = 0;
  send_zero (); // send the request for next bytes
  delay (100);

}

// Print the input data we have recieved
// accel data is 10 bits long
// so we read 8 bits, then we have to add
// on the last 2 bits.  That is why I
// multiply them by 2 * 2
void
print ()
{
  int joy_x_axis = outbuf[0];
  int joy_y_axis = outbuf[1];
  int accel_x_axis = outbuf[2] * 2 * 2; 
  int accel_y_axis = outbuf[3] * 2 * 2;
  int accel_z_axis = outbuf[4] * 2 * 2;

  int z_button = 0;
  int c_button = 0;

 // byte outbuf[5] contains bits for z and c buttons
 // it also contains the least significant bits for the accelerometer data
 // so we have to check each bit of byte outbuf[5]
  if ((outbuf[5] >> 0) & 1)
    {
      z_button = 1;
    }
  if ((outbuf[5] >> 1) & 1)
    {
      c_button = 1;
    }

  if ((outbuf[5] >> 2) & 1)
    {
      accel_x_axis += 2;
    }
  if ((outbuf[5] >> 3) & 1)
    {
      accel_x_axis += 1;
    }

  if ((outbuf[5] >> 4) & 1)
    {
      accel_y_axis += 2;
    }
  if ((outbuf[5] >> 5) & 1)
    {
      accel_y_axis += 1;
    }

  if ((outbuf[5] >> 6) & 1)
    {
      accel_z_axis += 2;
    }
  if ((outbuf[5] >> 7) & 1)
    {
      accel_z_axis += 1;
    }

  Serial.print (joy_x_axis, DEC);
  Serial.print ("\t");

  Serial.print (joy_y_axis, DEC);
  Serial.print ("\t");

  Serial.print (accel_x_axis, DEC);
  Serial.print ("\t");

  Serial.print (accel_y_axis, DEC);
  Serial.print ("\t");

  Serial.print (accel_z_axis, DEC);
  Serial.print ("\t");

  Serial.print (z_button, DEC);
  Serial.print ("\t");

  Serial.print (c_button, DEC);
  Serial.print ("\t");

  Serial.print ("\r\n");
// Blinky sequence
  if (z_button != 1) {
  allOFF();
  delay(1000);
  on(3,3); on(3,4); on(3,5); on(3,6);
  delay(400);
  allOFF();
  delay(1000);
  on(4,4); 
  delay(400);
  }
}

// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char
nunchuk_decode_byte (char x)
{
  x = (x ^ 0x17) + 0x17;
  return x;

}
