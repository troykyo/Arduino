// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

Servo servoA;  // create servo object to control a servo 
Servo servoB;  // a maximum of eight servo objects can be created 
Servo servoC1;
Servo servoC2;
Servo servoD1;
Servo servoD2;
//Servo servoE;

const int ledPin = 11;    // LED connected to digital pin 9

int pos = 0;    // variable to store the servo position 
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

int xPos = 0; //incoming serial byte
int yPos = 0; //incoming serial byte
int fadeValue = 0;    // LED connected to digital pin 9

const int  button1Pin = 14;    // the pin that the pushbutton is attached to
const int  button2Pin = 15;    // the pin that the pushbutton is attached to

int button1PushCounter = 0;   // counter for the number of button presses
int button1State = 0;         // current state of the button
int last1ButtonState = 0;     // previous state of the button
int button2PushCounter = 0;   // counter for the number of button presses
int button2State = 0;         // current state of the button
int last2ButtonState = 0;     // previous state of the button

void setup() 
{ 
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  Serial.begin(9600);
  servoA.attach(2);  // attaches the servo on pin to the servo object 
  servoB.attach(3);  // attaches the servo on pin to the servo object
  servoC1.attach(5);  // attaches the servo on pin to the servo object
  servoC2.attach(6);  // attaches the servo on pin to the servo object
  servoD1.attach(9);  // attaches the servo on pin to the servo object
  servoD2.attach(8);  // attaches the servo on pin to the servo object
 // servoE.attach(10);  // attaches the servo on pin to the servo object  


  for(pos = minpos; pos < maxpos; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servoA.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = maxpos; pos>=minpos; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servoA.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  Serial.print("A ");
  for(pos = minpos; pos < maxpos; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servoB.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = maxpos; pos>=minpos; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servoB.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  Serial.print("B ");

  for(pos = minCpos; pos < maxCpos; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servoC1.write(pos);              // tell servo to go to position in variable 'pos' 
    servoC2.write((abs(pos-180)));              // tell servo to go to position in variable 'pos' 
    Serial.print(pos); 
    Serial.print(" "); 
    delay(100);                       // waits 15ms for the servo to reach the position 
  } 
  Serial.println(" C ");
  for(pos = maxCpos; pos>=minCpos; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servoC1.write(pos);              // tell servo to go to position in variable 'pos' 
    servoC2.write((abs(pos-180)));              // tell servo to go to position in variable 'pos' 
    Serial.print(pos); 
    Serial.print(" "); 
    delay(100);                       // waits 15ms for the servo to reach the position 
  } 
  Serial.println(" C ");

  for(pos = maxDpos; pos>=minDpos; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servoD1.write(pos);              // tell servo to go to position in variable 'pos' 
    servoD2.write((abs(pos-180)));              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 

  Serial.print("D ");


  /*for(pos = minpos; pos < maxpos; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servoE.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waitsa

    for(pos = maxpos; pos>=minpos; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      servoE.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }   
    Serial.print("E ");
    */
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);         
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    } 

    // fade out from max to min in increments of 5 points:
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);         
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    } 
    Serial.println("* ");

    servoA.write(90);
    servoB.write(90);
    servoC1.write(90);
    servoC2.write(90);
    servoD1.write(90);
    servoD2.write(90);
    servoE.write(90);

  } 
}

void loop() { 
 
}
/*
  if (Serial.available() > 0) {
    Serial.flush(); //clear the buffer
    Serial.println("1"); // request Xpos
    // get incoming byte:
    xPos = Serial.read();
    Serial.println("2"); // request Xpos
    // get incoming byte:
    yPos = Serial.read();
    fadeValue = (xPos+yPos);
    analogWrite(ledPin, fadeValue);                          
  }
  servoC1.write(yPos);
  servoC2.write(abs(yPos-180));

  /*
  button1State = digitalRead(button1Pin);
   
   if (button1State != last1ButtonState) {
   // if the state has changed, increment the counter
   if (button1State == HIGH) {
   // if the current state is HIGH then the button
   // wend from off to on:
   button1PushCounter++;
   Serial.println("on");
   Serial.print("number of button 1 pushes:  ");
   Serial.println(button1PushCounter, DEC);
   } 
   else {
   // if the current state is LOW then the button
   // wend from on to off:
   Serial.println("1 off"); 
   }
   }
   button2State = digitalRead(button2Pin);
   if (button2State != last2ButtonState) {
   // if the state has changed, increment the counter
   if (button2State == HIGH) {
   // if the current state is HIGH then the button
   // wend from off to on:
   button2PushCounter++;
   Serial.println("on");
   Serial.print("number of button 2 pushes:  ");
   Serial.println(button2PushCounter, DEC);
   } 
   else {
   // if the current state is LOW then the button
   // wend from on to off:
   Serial.println("2 off"); 
   }
   }
   // save the current state as the last state, 
   //for next time through the loop
   last1ButtonState = button1State;
   last2ButtonState = button2State;
   */










