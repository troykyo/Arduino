/*---------------
 Color Cube
 Troy Nachtigall
 www.troykyo.com
 ---------------*/

#include <Wire.h>
#include "nunchuck_funcs.h"

byte xjoy,yjoy,accx,accy,accz,zbut,cbut; //wimote variables
byte xjoyLast,yjoyLast,accxLast,accyLast,acczLast,zbutLast,cbutLast; //more control variables
byte xjoyDefault,yjoyDefault; //even more control variables
int flash = 10; //controls the blink speed
int x = 5;
int y = 5;
unsigned long   timeDisplay = 0; //counter for the amount of time with no movement.
// Matrice, Somma, e Media
int RArray[smooth];
int BArray[smooth];
int GArray[smooth];
int RAverage = 0;   //  variable per la media 
int GAverage = 0;   //  variable per la media 
int BAverage = 0;   //  variable per la media 
int RAverageVecchio = 0;   // variable per la vecchia media
int GAverageVecchio = 0;   // variable per la vecchia media
int BAverageVecchio = 0;   // variable per la vecchia media
int ledpinR = 9;                           // light connected to digital pin 9
int ledpinG = 10;                           // light connected to digital pin 10 
int ledpinB = 11;                           // light connected to digital pin 11


// Ciclo, Base, Min e Max
int ciclo = 0; // contatore di cicli
int RBase = 0;  //Media di inizia
int GBase = 0;  //Media di inizia
int BBase = 0;  //Media di inizia
int RMax = 182;  //Max on X Axis
int GMax = 200;  //Max
int BMax = 200;  //Max
int RMin = 70;  //Min on X Axis
int GMin = 80;  //Min
int BMin = 70;  //Min


void setup() {
  Serial.begin(9600);
  nunchuck_setpowerpins();//analog 2 and 3 become power
  nunchuck_init(); // send the initilization handshake
  xjoyLast = -50; //reset Display Variables
  yjoyLast = -50;
  accxLast = -50;
  accyLast = -50;
  acczLast = -50;
  zbutLast = 0;
  cbutLast =0;

  delay (500); // wait before getting joystick defaults
  nunchuck_get_data(); //reads nunchuck
  xjoyDefault = nunchuck_joyx();//Sets WiiChuck Joystick Defaults
  yjoyDefault = nunchuck_joyy();


  Serial.println("GO!");
}


void loop() {
  for (int i = smooth-1; i >= 1; i--){
    RArray[i] = RArray[i-1]; //Sposta tutti i numeri adentro la matrice un posto 
    GArray[i] = GArray[i-1]; //Sposta tutti i numeri adentro la matrice un posto 
    BArray[i] = BArray[i-1]; //Sposta tutti i numeri adentro la matrice un posto 
  }
  readSensors();
  RArray[0] = accx;  //Aggiungere un nuovo lettura allo primo posto della matrice
  GArray[0] = accy;  //Aggiungere un nuovo lettura allo primo posto della matrice
  BArray[0] = accz;  //Aggiungere un nuovo lettura allo primo posto della matrice

  for (int i = 0; i < smooth; i++){
    RAverage += RArray[i]; //Somma la Matrice
    GAverage += GArray[i]; //Somma la Matrice
    BAverage += BArray[i]; //Somma la Matrice
  }
  RAverage = RAverage / smooth; //media della somma
  GAverage = GAverage / smooth; //media della somma
  BAverage = BAverage / smooth; //media della somma

  RBase = map(RAverage,RMin,RMax,0,255);
  GBase = map(GAverage,GMin,GMax,0,255);
  BBase = map(BAverage,BMin,BMax,0,255);

  if (RBase > RMax){//Each WiMote is slightly different.  This block adjusts the Max and Min brightness to the individual WiMote
    RMax = RBase;  
  }
  if (GBase > GMax){
    RMax = RBase;  
  }
  if (BBase > BMax){
    BMax = BBase;  
  }
  if (RBase > RMin){
    RMin = RBase;  
  }
  if (GBase > GMin){
    RMin = RBase;  
  }
  if (BBase > BMin){
    BMin = BBase;  
  }

  analogWrite(ledpinR, RBase);           // sets the value (range from 0 to 255) 
  analogWrite(ledpinG, GBase);           // sets the value (range from 0 to 255)
  analogWrite(ledpinB, BBase);           // sets the value (range from 0 to 255)  
  Serial.print("\tR: "); 
  Serial.print(RBase);
  Serial.print("\tG: "); 
  Serial.print(GBase);
  Serial.print("\tB: "); 
  Serial.print(BBase);
  Serial.print("\tCiclo: "); 
  Serial.print(ciclo);
   Serial.print("\tTime: "); 
  Serial.println(millis());
  ciclo ++;
  
}

void readSensors() {
reread:
  nunchuck_get_data(); //reads nunchuck
  accx  = nunchuck_accelx(); // ranges from approx 70 - 182
  accy  = nunchuck_accely(); // ranges from approx 80 - 200
  accz  = nunchuck_accelz(); // ranges from approx 78 - 200
  xjoy = nunchuck_joyx();
  yjoy = nunchuck_joyy();


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





