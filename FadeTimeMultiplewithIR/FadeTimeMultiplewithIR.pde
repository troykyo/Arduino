#include <IRremote.h>
IRsend irsend;

const int led[] = {
  -1,12,5,6,9,10,11};// PWM Pins that the LEDs are attached too.
int fadeLevel;       //counter for fading 
int fadeTime[] = {
  -1,0,0,0,0,0,0}; //Time for a fade in Milliseconds
unsigned long startTime[] = {
  -1,0,0,0,0,0,0};    // the  time the interaction started
unsigned int sendTime[] = {
  400,400,400,400,100,400,200};//array to send 
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long syncTime = 0;    // the  time the interaction started


void setup() {  

  pinMode(13, OUTPUT);  
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
  for (int i = 1;i<7;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but effications
    fadeTime[i] = random(1000,10000);
    startTime[i] = millis(); //Time the 
  }
  currentTime = millis(); //What time is it right now 
}

void loop(){
  digitalWrite (13,HIGH);
  for (int i = 1;i<7;i++){
    if ((abs(currentTime-startTime[i]))<(fadeTime[i]/2)) {//fade up for half of the fade time
      currentTime = millis(); //What time is it right now 
      fadeLevel = map((currentTime-startTime[i]),0,(fadeTime[i]/2),0,255);
      // Serial.print((currentTime-startTime[i]));
      //Serial.print(" ");
      analogWrite(led[i], fadeLevel); 
    }
    if ((abs(currentTime-startTime[i]))<(fadeTime[i])&&(abs(currentTime-startTime[i]))>(fadeTime[i]/2))  {//fade down for half of the fade time
      currentTime = millis(); //What time is it right now 
      fadeLevel = map((currentTime-startTime[i]),(fadeTime[i]/2),fadeTime[i],0,255);
      //Serial.print((currentTime-startTime[i]));
      //Serial.print(" ");
      analogWrite(led[i], (255-fadeLevel)); 
      digitalWrite (13,LOW);
    }
    if ((abs(currentTime-startTime[i]))>(fadeTime[i])) {//fade up for half of the fade time
      fadeTime[i] = random(1000,10000);
      sendTime[4] = fadeTime[i];
      startTime[i] = millis(); //Time the 
      currentTime = millis(); //What time is it right now 
      Serial.print(" ");
      Serial.print(fadeTime[2]);
     // irsend.sendRaw(sendTime,6,36); // Sony TV power code
      delay(100);
      irsend.sendSony(0xa90, 12); // Sony TV power code
    }
  }
}








