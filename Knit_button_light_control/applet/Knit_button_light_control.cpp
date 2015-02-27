/*
 SAM Io Abito :: Next Light
 This is the code for controling 14 lights for a opening show at the SAM art Space
 http://www.troykyo.com
 */
#include "WProgram.h"
void buttonoff();
void setup();
void loop ();
int ledpin[] = { 
  9,10,11};   // an array of pin numbers to Which LEDs are attached
int inPin[] = { 
  2,3,4,5};   // an array of pin numbers to Which Buttons are attached
int inVar[] = { 
  1,2,3,4};   // an array of Values to Which Buttons communicate  
int Value[] = { 
  1,2,3};   // an array of Values to Which LEDs brightness are attached
int Which1 = 0;               // Random Control 1
int Which2 = 0;               // Random Control 2
int Which3 = 0;               // Random Control 3
int time = 0;                 // time control 1
int inTime = 0;               // last time button was pressed
int Value1 = 0;                // Red PWM intensity
int Value2 = 0;               // Green PWM intensity
int Value3 = 0;                // Blue PWM intensity

void buttonoff()           // turns LED on or off is pressed for less than 1 second, fades up, then down if more than 1 second
{  
  time == millis();
  while ((time < 1000)) {
  (inVar[Which2]) = digitalRead((inPin[Which1]));  // read input Value
  //Serial.print("Ready "); 
  if ((inVar[Which2]) == LOW) {            // check if the input is LOW 
    if ((ledpin[Which1]) == HIGH){
      digitalWrite(ledpin[Which1], LOW);  // turn LED off
      }
    else{
      digitalWrite(ledpin[Which1], LOW);  // turn LED ON
      } 
    break;
    }
    Serial.print("Fading");
    } 
  for((Value[Which2]); (Value[Which2]) <= 255; (Value[Which2])+=1) // fade in (from min to max) 
    { 
      analogWrite((ledpin[Which1]), Value[Which2]);           // sets the Value (range from 0 to 255) 
      if (inVar == LOW) {            // check if the input is LOW 
      break;
    }
    delay(1);                            // waits for 30 milli seconds to see the dimming effect 
  }
  for((Value[Which2]); (Value[Which2]) >= 0; (Value[Which2])-=1) // fade in (from min to max) 
  { 
      analogWrite((ledpin[Which1]), Value[Which2]);           // sets the Value (range from 0 to 255) 
      if (inVar == LOW) {            // check if the input is LOW 
      break;
    }
    delay(1);
  }
    
}

void setup()                    
{
Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

  pinMode(ledpin[9] , OUTPUT);
  pinMode(ledpin[10], OUTPUT);
  pinMode(ledpin[11], OUTPUT);
  pinMode(inPin[1], INPUT);
  pinMode(inPin[2], INPUT);
  pinMode(inPin[3], INPUT);
  pinMode(inPin[4], INPUT);
}


void loop () {
inVar[1] = digitalRead(inPin[2]);  // read input Value
inVar[2] = digitalRead(inPin[3]);  // read input Value
inVar[3] = digitalRead(inPin[4]);  // read input Value
inVar[4] = digitalRead(inPin[5]);  // read input Value
  time == 0;
  if (inVar[1] == HIGH) {            // check if the input is HIGH   
    Serial.print("1");
    Which1 == 9;
    Which2 == 1;
    buttonoff();
  }  
  else if (inVar[2] == HIGH) {            // check if the input is HIGH   
    Serial.print("2");
    Which1 == 10;
    Which2 == 2; 
    buttonoff();
  }
  else if (inVar[3] == HIGH) {            // check if the input is HIGH   
    Serial.print("3");
    Which1 == 11;
    Which2 == 3; 
    buttonoff();
  }
  else if (inVar[4] == HIGH) {            // check if the input is HIGH   
    Serial.print("4");
    if (Value[1] > 0 || Value[2] > 0 || Value[3] > 0) {
            Value[1] == 0;
            Value[2] == 0;
            Value[3] == 0;
            analogWrite(ledpin[9], Value[1]);           // sets the Value (range from 0 to 255) 
            analogWrite(ledpin[10], Value[2]);           // sets the Value (range from 0 to 255)
            analogWrite(ledpin[11], Value[3]);           // sets the Value (range from 0 to 255)  
    } 
    else{
            Value[1] == 255;
            Value[2] == 255;
            Value[3] == 255;
            analogWrite(ledpin[9], Value[1]);           // sets the Value (range from 0 to 255) 
            analogWrite(ledpin[10], Value[2]);           // sets the Value (range from 0 to 255)
            analogWrite(ledpin[11], Value[3]);           // sets the Value (range from 0 to 255) 
    }  
  }      
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

