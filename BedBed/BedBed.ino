

#include <Wire.h>

#include "nunchuck_funcs.h"

int loop_cnt=0;

byte accx,accy,accz,zbut,cbut,cambia;
byte lastaccx=126;
byte lastaccy=126;
byte lastaccz=126;

int sogliaMin = 4;
int soglia = 20;
int sogliaMax = 35;

const int led[] = {
  -1,11,5,6,9};// PWM Pins that the LEDs are attached too.
int fadeLevel;       //counter for fading 
int i;
int x = 0;
int fadeTime[] = {
  -1,0,0,0,0,0,0}; //Time for a fade in Milliseconds
unsigned long startTime[] = {
  -1,0,0,0,0,0,0};    // the  time the interaction started
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long syncTime = 0;    // the  time the interaction started
unsigned long tempoMassimo = 1000;    // the  time the interaction started
unsigned long startMassimo = 1000;    // the  time the interaction started

void setup() {  

  pinMode(13, OUTPUT);  
  Serial.begin(19200);
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake

  Serial.print("WiiChuckDemo ready\n");
  for (int i = 1;i<5;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but effications
    fadeTime[i] = random(1000,10000);
    startTime[i] = millis(); //Time the 
  }
  currentTime = millis(); //What time is it right now 
}

void loop(){
  move();
  if (cambia <= sogliaMin){
    analogWrite(led[1],0);
    analogWrite(led[2],0);
    analogWrite(led[3],0);
    analogWrite(led[4],0);
    move();  
  }
  else if ((cambia > sogliaMin) && (cambia <= soglia)){  
    moving();
  }
  else if ((cambia > soglia) && (cambia <= sogliaMax)){  
    Party();
  }
  else if (cambia > sogliaMax){  
    freaky();
  }  
}


void moving(){
  Serial.println("\tMoving");
  currentTime = millis(); //What time is it right now 
  for (i = 1;i<5;i++){
    Serial.print(i);
    fadeTime[i]=random(1000,3000);
    if (fadeTime[i]>fadeTime[(i-1)]){
      tempoMassimo = fadeTime[i];
      startMassimo = startTime[i];
    }
  }
  currentTime = millis(); //What time is it right now 
  tempoMassimo = 1000+currentTime;
  do  {
    for (i = 1;i<5;i++){
   
      currentTime = millis(); //What time is it right now 
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

      }
      if ((abs(currentTime-startTime[i]))>(fadeTime[i])) {//fade up for half of the fade time
        fadeTime[i] = random(1000,10000);
        startTime[i] = millis(); //Time the 
        currentTime = millis(); //What time is it right now 
        Serial.print(" ");
        Serial.print(i);
        Serial.print(" ");
        Serial.print(fadeTime[i]);
      }
    }
  }
  while (currentTime < tempoMassimo);
}

void Party() {
  Serial.println("\tParty");
  digitalWrite (13,HIGH);
  fadeTime[1] = random(500,1000);
  startTime[1] = millis();
  startTime[2] = startTime[1]+1000;
  startTime[3] = startTime[2]+1000;
  startTime[4] = startTime[3]+1000;

  do  {
    move();
    for (i = 1;i<5;i++){
      currentTime = millis(); //What time is it right now 
      if (currentTime>startTime[i]){
        if ((abs(currentTime-startTime[i]))<(fadeTime[1]/2)) {//fade up for half of the fade time
          currentTime = millis(); //What time is it right now 
          fadeLevel = map((currentTime-startTime[i]),0,(fadeTime[i]/2),0,255);
          // Serial.print((currentTime-startTime[i]));
          //Serial.print(" ");
          analogWrite(led[i], fadeLevel); 
        }
        if ((abs(currentTime-startTime[i]))<(fadeTime[1])&&(abs(currentTime-startTime[i]))>(fadeTime[i]/2))  {//fade down for half of the fade time
          currentTime = millis(); //What time is it right now 
          fadeLevel = map((currentTime-startTime[i]),(fadeTime[1]/2),fadeTime[1],0,255);
          //Serial.print((currentTime-startTime[i]));
          //Serial.print(" ");
          analogWrite(led[i], (255-fadeLevel)); 
          digitalWrite (13,LOW);
        }
        if ((abs(currentTime-startTime[i]))>(fadeTime[1])) {//fade up for half of the fade time
          startTime[i] = millis(); //Time the 
          currentTime = millis(); //What time is it right now 
          Serial.print(" ");
          Serial.print(i);
          Serial.print(" ");
          Serial.print(fadeTime[i]);
        }
      }
    }
  }
  while ((cambia >sogliaMin)&& (cambia<=soglia));

}
void freaky(){
  Serial.println("\tFreaky");
  digitalWrite (13,HIGH);

  for (i = 1;i<5;i++){
    currentTime = millis(); //What time is it right now 
    if ((abs(currentTime-startTime[i]))>(fadeTime[i])) {//fade up for half of the fade time
      fadeTime[i] = random(30,50);
      startTime[i] = millis(); //Time the 
      currentTime = millis(); //What time is it right now 
      analogWrite(led[i], (random (0, 255))); 
      Serial.print(" ");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(fadeTime[i]);
    }
  }
}  

void move()
{
  currentTime = millis(); //What time is it right now 
  if( currentTime - loop_cnt > 50 ) { // 50 sec lag
    loop_cnt = millis();

    nunchuck_get_data();

    accx  = nunchuck_accelx(); // ranges from approx 70 - 182
    accy  = nunchuck_accely(); // ranges from approx 65 - 173
    accz  = nunchuck_accelz(); // ranges from approx 65 - 173
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton(); 
    cambia = abs(accx-lastaccx)+abs(accy-lastaccy)+abs(accz-lastaccz);     
    lastaccx=accx;
    lastaccy=accy;
    lastaccz=accz;
    Serial.print("cambia: "); 
    Serial.print((byte)cambia,DEC); 
    Serial.print("\taccx: "); 
    Serial.print((byte)accx,DEC);
    Serial.print("\taccy: "); 
    Serial.print((byte)accy,DEC);
    Serial.print("\taccz: "); 
    Serial.print((byte)accz,DEC);
    Serial.print("\tzbut: "); 
    Serial.print((byte)zbut,DEC);
    Serial.print("\tcbut: "); 
    Serial.println((byte)cbut,DEC);
  }
}

