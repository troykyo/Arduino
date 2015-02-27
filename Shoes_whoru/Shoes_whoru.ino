const int numReadings = 10;
int index = 0;                  // the index of the current reading

int butt1[numReadings];      // the readings from the analog input
int butt2[numReadings];      // the readings from the analog input
int butt3[numReadings];      // the readings from the analog input
int butt4[numReadings];      // the readings from the analog input
int total1 = 0;                  // the running total
int total2 = 0;                  // the running total
int total3 = 0;                  // the running total
int total4 = 0;                  // the running total
int average1 = 0;                // the average
int average2 = 0;                // the average
int average3 = 0;                // the average
int average4 = 0;                // the average

const int led[] = {
  -1,3,5,6,9,10,11};// PWM Pins that the LEDs are attached too.
const int butt[] = {
  -1,A0,A1,A2,A3,A4,A5};// PWM Pins that the LEDs are attached too.  
int fadeLevel;       //counter for fading  Z
long fadeTime[] = {
  -1,0,0,0,0,0,0}; //Time for a fade in Milliseconds
long startTime[] = {
  -1,0,50,100,150,200,250};    // the  time the interaction started
long mode[10];    // the  time the interaction started

unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long syncTime = 0;    // the  time the interaction started
int maxfade = 128 ;
long masterStartTime = 0;

void setup() {  

  pinMode(13, OUTPUT);  
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
  for (int i = 1;i<7;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but effications
    pinMode(butt[i], OUTPUT); //declare all the buttons as inputs
    digitalWrite(butt[i], HIGH); // set the inernal pull up resistor.
    //fadeTime[i] = random(1000,10000);
    fadeTime[i] = 1000;
    startTime[i] = 50*i;
    masterStartTime = millis(); //Time the sequesnce started 
  }
  currentTime = millis(); //What time is it right now 
}

void loop(){
  digitalWrite (13,HIGH);
  
  
  for (int i = 1;i<7;i++){
    if (((currentTime-masterStartTime) < (fadeTime[i]/2)) && ((currentTime - masterStartTime - startTime[i]) > 0))  {//fade up for half of the fade time

      currentTime = millis(); //What time is it right now 
      fadeLevel = map((currentTime-masterStartTime-startTime[i]),0,(fadeTime[i]/2),0,maxfade);
      // Serial.print((currentTime-startTime[i]));
      //Serial.print(" ");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(fadeLevel);
      Serial.print(" ");
      if (fadeLevel > 0 && fadeLevel < 255){
        analogWrite(led[i], fadeLevel);
        currentTime = millis(); //What time is it right now   
      } 
      currentTime = millis(); //What time is it right now 

    }


      if ((currentTime-masterStartTime - startTime[i] ) > (fadeTime[i]/2))  {//fade up for half of the fade time
      currentTime = millis(); //What time is it right now 
      fadeLevel = map((currentTime-masterStartTime-startTime[i]),fadeTime[i],(fadeTime[i]/2),0,maxfade);
      Serial.print(i);
      Serial.print(" ");
      Serial.print(fadeLevel);
      Serial.print(" ");
      if (fadeLevel > 0 && fadeLevel < 255){
        analogWrite(led[i], fadeLevel);
        currentTime = millis(); //What time is it right now   
      } 
      currentTime = millis(); //What time is it right now 

    }
    /* if (((currentTime-(masterStartTime-startTime[i])))<(fadeTime[i])&&(abs(currentTime-(masterStartTime-startTime[i])))>(fadeTime[i]/2))  {//fade down for half of the fade time
     currentTime = millis(); //What time is it right now 
     fadeLevel = map((currentTime-startTime[i]),(fadeTime[i]/2),fadeTime[i],0,maxfade);
     //Serial.print((currentTime-startTime[i]));
     //Serial.print(" ");
     if (fadeLevel > 0 && fadeLevel < 255){
     
     analogWrite(led[i], (maxfade-fadeLevel)); 
     }
     digitalWrite (13,LOW);
     }
     */

  }



  currentTime = millis(); //What time is it right now 

  if ((currentTime - masterStartTime)>1500 ){
    masterStartTime = millis(); //Time the right now
    currentTime = millis(); //What time is it right now 
  }
  Serial.println("*");


}

void footsteps(){
  for (int i = 0;i<10;i++){
                      
    butt1[i] = analogRead(butt[i]);
    total1 = total2 + butt1[i];
    butt2[i] = analogRead(butt[i]);
    total2 = total2 + butt2[i];     
    butt3[i] = analogRead(butt[i]);
    total3 = total3 + butt3[i];
    butt4[i] = analogRead(butt[i]);
    total4 = total4 + butt4[i]; 
    
    
    
    


 









