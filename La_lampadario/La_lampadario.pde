#include <Sprite.h>
#include <Matrix.h>
#include <Servo.h>
int minpos = 0;
int maxpos = 180;
int pos;
int rate = 1;
int button[] = {
  A0,A1,A2,A3,A4,A5};
int buttonstate[] = {
  200,200,200,200,200,200};
int troy = 0;
int randT = 0;


// La Lampadario
// by T. Robert Nachtigall www.troykyo.com


// 

/* create a new Matrix instance
 pin 0: data  (din)
 pin 3: load  (load) //Green
 pin 4: clock (clk) // Yellow
 */
Matrix myMatrix1 = Matrix(7, 3, 4);
Matrix myMatrix2 = Matrix(6, 3, 4);
Servo servo;  // create servo object to control servoA
void setup()
{
  servo.attach(12);  // attaches the servo on pin sA to the servo object
  for (int thisPin = 0; thisPin < 7; thisPin++) {
    pinMode(thisPin, OUTPUT);
    for (int i = 0; i < 6; i++)  {
      pinMode(button[i], INPUT); 
      myMatrix1.clear(); // clear display
      myMatrix2.clear(); // clear display
      // turn some pixels on
      for (int x=1;x<9;x+2){
        myMatrix1.write(1, x, HIGH);
        myMatrix1.write(2, x, HIGH);
        myMatrix2.write(1, x, HIGH);
        myMatrix2.write(2, x, HIGH);
        delay (1000);
      }
    }
  }
}
  void loop()
  {

    for (int x = 0; x < 6; x++) {    
      int reading = analogRead(button[x]); // read the state of the switch into a local variable:
      if (reading < 100) { // If the switch changed, due to noise or pressing:   
        troy = troy++; // stepcase
        if (troy == 5){
          troy == 0;
        }
      }
    } 

    switch (troy) {
    case 0:    // your hand is on the sensor
      myMatrix1.clear(); // clear display
      myMatrix2.clear(); // clear display
      // turn some pixels on
      for (int x=1;x<9;x+2){
        myMatrix1.write(1, x, HIGH);
        myMatrix1.write(2, x, HIGH);
        myMatrix2.write(1, x, HIGH);
        myMatrix2.write(2, x, HIGH);
      }
      servo.write(0);              // tell servo to go to position in variable 'pos' 
      delay (500);
      myMatrix1.clear(); // clear display
      myMatrix2.clear(); // clear display
      // turn some pixels on
      for (int x=0;x<9;x+2){
        myMatrix1.write(1, x, HIGH);
        myMatrix1.write(2, x, HIGH);
        myMatrix2.write(1, x, HIGH);
        myMatrix2.write(2, x, HIGH); 
      }  
      servo.write(180);              // tell servo to go to position in variable 'pos' 
      delay (500);    
      break;  
    case 1:    // your hand is on the sensor
      myMatrix1.clear(); // clear display
      myMatrix2.clear(); // clear display
      // turn some pixels on
      for (int x=1;x<9;x+1){
        myMatrix1.write(1, x, HIGH);
        myMatrix1.write(2, x, HIGH);
        myMatrix2.write(1, x, HIGH);
        myMatrix2.write(2, x, HIGH);
      }
      servo.write(0);              // tell servo to go to position in variable 'pos' 
      delay (500);
      myMatrix1.clear(); // clear display
      myMatrix2.clear(); // clear display
      // turn some pixels on
      for (int x=0;x<9;x+2){
        myMatrix1.write(1, x, HIGH);
        myMatrix1.write(2, x, HIGH);
        myMatrix2.write(1, x, HIGH);
        myMatrix2.write(2, x, HIGH); 
      }  
      servo.write(180);              // tell servo to go to position in variable 'pos' 
      delay (500);    
      break;
    case 2:    // your hand is on the sensor
      myMatrix1.clear(); // clear display
      myMatrix2.clear(); // clear display
      // turn some pixels on
      for (int x=1;x<9;x+2){
        randT = random(0,8);
        myMatrix1.write(1, randT, HIGH);
        myMatrix1.write(2, randT, HIGH);
        myMatrix2.write(1, randT, HIGH);
        myMatrix2.write(2, randT, HIGH); 
      }
      servo.write(0);              // tell servo to go to position in variable 'pos' 
      delay (500);
      myMatrix1.clear(); // clear display
      myMatrix2.clear(); // clear display
      // turn some pixels on
      for (int x=0;x<9;x+2){
        randT = random(0,8);
        myMatrix1.write(1, randT, HIGH);
        myMatrix1.write(2, randT, HIGH);
        myMatrix2.write(1, randT, HIGH);
        myMatrix2.write(2, randT, HIGH); 
      }  
      servo.write(180);              // tell servo to go to position in variable 'pos' 
      delay (500);    
      break;
    }
  }


