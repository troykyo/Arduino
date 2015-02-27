/*
 *SAM Io Abito :: Next Light
 *
 *This is the code for controling 14 lights for a show at the SAM art Space
 *
 * http://www.troykyo.com
 */
#include "WProgram.h"
void changeLight();
void testPattern ();
void setup();
void loop ();
int led[] = { 
  0,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };   // an array of pin numbers to which LEDs are attached
int inPin = 19;               // Button 
int inVar = 0;                // Variable for Button Control
int Which1 = 0;               // Random Control 1
int Which2 = 0;               // Random Control 2
int Which3 = 0;               // Random Control 3
int time = 0;                 // time control 1
int inTime = 0;               // last time button was pressed

void changeLight()           // Main Prgrm
{  
  time == millis();
  while ((time - inTime) < 300000) {
  inVar = digitalRead(inPin);  // read input value
  //Serial.print("Ready "); 
  if (inVar == HIGH) {            // check if the input is HIGH 
    testPattern();
    Which1 = random(2,15);   
    digitalWrite(led[Which1], HIGH);  // turn LED ON
    //digitalWrite(led[Which2], HIGH);  // turn LED ON
    //digitalWrite(led[Which2], LOW);  // turn LED OFF
    Serial.print(Which1); 
    //delay(2000);                  // waits for 2 seconds  
    Which2 == Which1;
    Which3 == Which2;
    inTime == millis();
    } 
  }
}
void testPattern ()
{
for (int i = 0; i < 16; i++) {
       digitalWrite(led[i], HIGH);  // turn LED ON
       digitalWrite(led[i-1], LOW);  // turn LED OFF
       delay(100);                  // waits for 1/3 second 
    }
}

void setup()                    
{
Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

  pinMode(led[15], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(led[4], OUTPUT);
  pinMode(led[5], OUTPUT);
  pinMode(led[6], OUTPUT);
  pinMode(led[7], OUTPUT);
  pinMode(led[8], OUTPUT);
  pinMode(led[9], OUTPUT);
  pinMode(led[10], OUTPUT);
  pinMode(led[11], OUTPUT);
  pinMode(led[12], OUTPUT);  
  pinMode(led[13], OUTPUT);
  pinMode(led[14], OUTPUT);
  pinMode(inPin, INPUT); 
}


void loop () {
inVar = digitalRead(inPin);  // read input value
  time == 0;
  inTime == 0;
  
  if (inVar == HIGH) {            // check if the input is HIGH   
    Serial.print("begin"); 
    changeLight ();
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

