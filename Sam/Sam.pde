/*
 *SAM Io Abito :: Next Light
 *
 *This is the code for controling 14 lights for a show at the SAM art Space
 *
 * http://www.troykyo.com
 */
int led[] = { 
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };   // an array of pin numbers to which LEDs are attached
int inPin = 15;              // Button 
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
    Which1 = random(1,14);   
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
for (int i = 0; i < 15; i++) {
       digitalWrite(led[i], HIGH);  // turn LED ON
       digitalWrite(led[i-1], LOW);  // turn LED OFF
       delay(100);                  // waits for 1/3 second 
    }
}

void setup()                    
{
Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

  pinMode(led[Which1], OUTPUT);
  pinMode(led[Which2], OUTPUT);
  pinMode(led[Which3], OUTPUT);
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
