/*
  La Lampada Curioso
 
 */

#include <Servo.h>

//Servos and constants
const int sA = 2;      // the pin that servoA is attached too
const int sB = 3;      // the pin that servoB is attached too
const int sC1 = 5;      // the pin that servoC is attached too
const int sC2 = 6;      // the pin that servoC is attached too
const int sD1 = 8;      // the pin that servoD is attached too
const int sD2 = 9;      // the pin that servoD is attached too
const int sE = 10;      // the pin that servoE is attached too
const int ledPin = 11;    // LED connected to digital pin 9

Servo servoA;  // create servo object to control a servo 
Servo servoB;  // a maximum of eight servo objects can be created 
Servo servoC1;
Servo servoC2;
Servo servoD1;
Servo servoD2;
Servo servoE;

int minpos = 0;
int maxpos = 180;
int minApos = 0;
int maxApos = 180;
int minBpos = 0;
int maxBpos = 180;
int minCpos = 60;
int maxCpos = 170;
int minDpos = 50;
int maxDpos = 170;
int minEpos = 0;
int maxEpos = 180;

int pos[] = {
  -1,90,90,90,90,90};    // variable to store the servo position
int des[] = {
  -1,90,90,90,90,90};    
;    // variable to store the servo destination
int butdes[] = {
  -1,90,90,90,90,90};
;    // variable to store the button press servo destination

int xPos = 320; //Horizontlal position passed from the Kinect
int yPos = 320; //Vertical position passed from the Kinect

int movedelay = 10;
int inputdelay =1000;
int needstep = 1; //counter for needinput
int needmax = 6; //Matrix Max
int needA[] = { 
  60, 70, 80, 90, 100, 160 };
int needB[] = { 
  60, 70, 80, 90, 100, 160 };
int needC[] = { 
  60, 70, 80, 90, 100, 160 };
int needD[] = { 
  60, 70, 80, 90, 100, 160 };
int needE[] = { 
 60, 70, 80, 90, 100, 160 };

int touchA[] = { 
  2, 7, 4, 6, 5, 3, 3, 5 };
int touchB[] = { 
  2, 7, 4, 6, 5, 3, 3, 5 };
int touchC[] = { 
  2, 7, 4, 6, 5, 3, 3, 5 };
int touchD[] = { 
  2, 7, 4, 6, 5, 3, 3, 5 };
int touchE[] = { 
  2, 7, 4, 6, 5, 3, 3, 5 };
int touchF[] = { 
  2, 7, 4, 6, 5, 3, 3, 5 };

//Buttons
int buttonpin[] = { 
  14, 15 }; 
int buttonstate[] = { 
  0, 0};
int lastbuttonstate [] = { 
  0, 0};
long lastdebouncetime[] = {
  0, 0};  // the last time the output pin was toggled
long debouncedelay = 50;    // the debounce time; increase if the output flickers

void setup()
{
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the ledPin as an output:
  servoA.attach(sA);  // attaches the servo on pin sA to the servo object
  servoB.attach(sB);  // attaches the servo on pin sB to the servo object
  servoC1.attach(sC1);  // attaches the servo on pin sC to the servo object
  servoC2.attach(sC2);  // attaches the servo on pin sC to the servo object
  servoD1.attach(sD1);  // attaches the servo on pin sD to the servo object
  servoD2.attach(sD2);  // attaches the servo on pin sD to the servo object
  servoE.attach(sE);  // attaches the servo on pin SE to the servo object  
 
  digitalWrite(ledPin, HIGH);   // set the LED on
 
  for (int i = 0; i < 8; i++)  {
    pinMode(buttonpin[i], INPUT);      
  }
}

void touchme(){
  for (int x = 0; x < 1; x++) {    
    int reading = analogRead(buttonpin[x]); // read the state of the switch into a local variable:
    if (reading < 100) { // If the switch changed, due to noise or pressing:   
      lastdebouncetime[x] = millis(); // reset the debouncing timer
    } 
    if ((millis() - lastdebouncetime[x]) > debouncedelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:
      buttonstate[x] = reading;
    }
    lastbuttonstate[x] = reading;  // save the reading to last button state

    if (buttonstate[x] == HIGH){ //Move according to which button is pressed

      if ((pos[x] > touchA[x])){ //Test to see which button is pressed
        pos[x]--; //increment 
        servoA.write(pos[x]); //Tell the servo to Move
      }
      else if (pos[x] < touchA[x]){ //Test if the actual and desired positions are equal
        pos[x]++; //increment 
        servoA.write(pos[x]); //Tell the servo to Move
      }
      if ((pos[x] > touchB[x])){ //Test to see which button is pressed
        pos[x]--; //increment 
        servoB.write(pos[x]);}
      else if (pos[x] < touchB[x]){ //Test if the actual and desired positions are equal
        pos[x]++; //increment 
        servoB.write(pos[x]); //Tell the servo to Move      
      }
      if ((pos[x] > touchC[x])){ //Test to see which button is pressed
        pos[x]--; //increment 
        servoC1.write(pos[x]); //Tell the servo to Move
      }
      else if (pos[x] < touchC[x]){ //Test if the actual and desired positions are equal
        pos[x]++; //increment 
        servoC1.write(pos[x]); //Tell the servo to Move
      }
      if ((pos[x] > touchD[x])){ //Test to see which button is pressed
        pos[x]--; //increment 
        servoD1.write(pos[x]); //Tell the servo to Move
      }
      else if (pos[x] < touchD[x]){ //Test if the actual and desired positions are equal
        pos[x]++; //increment 
        servoD1.write(pos[x]); //Tell the servo to Move
      }
      if ((pos[x] > touchE[x])){ //Test to see which button is pressed
        pos[x]--; //increment  b b
        servoE.write(pos[x]); //Tell the servo to Move
      }
      else if (pos[x] < touchE[x]){ //Test if the actual and desired positions are equal
        pos[x]++; //increment 
        servoE.write(pos[x]); //Tell the servo to Move  
      }
      /*Serial.print(pos[x]);
      Serial.print(" ");
      Serial.print(x);
      Serial.print(touchA[x]);
      Serial.print(" | ");
*/
    }
  }
}




void moveservo(){
  //Serial.println("Spostamento Iniziato");
  while ((pos[1]!=des[1]) && (pos[2]!=des[2]) && (pos[3]!=des[3]) && (pos[4]!=des[4]) && (pos[5]!=des[5])){
      if (pos[1] > des[1]){ //Test if the actual and desired positions are equal
        pos[1]--; //increment 
        servoA.write(pos[1]);
        delay (movedelay);
      } //Tell the servo to Move
      if (pos[1] < des[1]){ //Test if the actual and desired positions are equal
        pos[1]++; //increment 
        servoA.write(pos[1]); //Tell the servo to Move
        delay(movedelay);
      }
      if (pos[2] > des[2]){ //Test if the actual and desired positions are equal
        pos[2]--; //increment 
        servoB.write(pos[2]);
        delay (movedelay);
      } //Tell the servo to Move
      if (pos[2] < des[2]){ //Test if the actual and desired positions are equal
        pos[2]++; //increment 
        servoB.write(pos[2]); //Tell the servo to Move
        delay(movedelay);
      }
      if (pos[3] > des[3]){ //Test if the actual and desired positions are equal
        pos[3]--; //increment 
        servoC1.write(pos[3]);
        servoC2.write(abs((pos[3]-180)));
        delay (movedelay);
      } //Tell the servo to Move
      if (pos[3] < des[3]){ //Test if the actual and desired positions are equal
        pos[3]++; //increment 
        servoC1.write(pos[3]); //Tell the servo to Move
        servoC2.write(abs((pos[3]-180)));
        delay(movedelay);
      }
     if (pos[4] > des[4]){ //Test if the actual and desired positions are equal
        pos[4]--; //increment 
        servoD1.write(pos[4]);
        servoD2.write(abs((pos[4]-180)));
        delay (movedelay);
      } //Tell the servo to Move
      if (pos[4] < des[4]){ //Test if the actual and desired positions are equal
        pos[4]++; //increment 
        servoD1.write(pos[4]); //Tell the servo to Move
        servoD2.write(abs((pos[4]-180)));
        delay(movedelay);
      }  
      if (pos[5] > des[5]){ //Test if the actual and desired positions are equal
        pos[5]--; //increment 
        servoE.write(pos[5]);
        delay (movedelay);
      } //Tell the servo to Move
      if (pos[5] < des[5]){ //Test if the actual and desired positions are equal
        pos[5]++; //increment 
        servoA.write(pos[5]); //Tell the servo to Move
        delay(movedelay);
      }
      
      touchme();    
  }
} 


void scratchme(){

}


void lookaround() {
  if (Serial.available() > 0) {
    Serial.flush(); //clear the buffer
    Serial.println("1"); // request Xpos
    // get incoming byte:
    xPos = Serial.read();
    Serial.println("2"); // request Xpos
    // get incoming byte:
    yPos = Serial.read();
    des[1] = map(xPos, 0, 128, minApos, maxApos);
    des[2] = map(yPos, 0, 128, minBpos, maxBpos);
    des[3] = map(yPos, 0, 128, minCpos, maxCpos);
    des[4] = map(yPos, 0, 128, minDpos, maxDpos);
    des[5] = map(xPos, 0, 128, minEpos, maxEpos);
  }
  else{
    needinput();
  }
}
void needinput(){
  // Gets a new pose
  des[1] = needA[needstep]; 
  des[2] = needB[needstep];
  des[3] = needC[needstep];
  des[4] = needD[needstep];
  des[5] = needE[needstep];  
  needstep++;
  if (needstep > needmax) 
    needstep = 1;
  moveservo();
  delay(1000);
}



void loop() {
puppyreset: 
  lookaround();
  moveservo();
}









