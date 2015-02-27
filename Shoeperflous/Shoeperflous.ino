const int numReadings = 10;
const int numSteps = 10;
int index = 0;                  // the index of the current reading

int buttonTime1[numReadings];      // the readings from the analog input
int buttonTime2[numReadings];      // the readings from the analog input
int total1 = 0;                  // the running total
int total2 = 0;                  // the running total
int average1 = 0;                // the average
int average2 = 0;                // the average
unsigned long stepTime1[numSteps];
unsigned long stepTime2[numSteps];
int j = 0;

const int led[] = {
  -1,3,5,6,9,10,11};// PWM Pins that the LEDs are attached too.
const int butt1 = 14;
const int butt2 = 15;

int fadeLevel;       //counter for fading  Z
long fadeTime[] = {
  -1,0,0,0,0,0,0}; //Time for a fade in Milliseconds
long startTime[] = {
  -1,0,50,100,150,200,250};    // the  time the interaction started
int mode;

unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long syncTime = 0;    // the  time the interaction started
int maxfade = 128 ;
long masterStartTime = 0;

void setup() {  
  pinMode(13, OUTPUT);  
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
  pinMode(butt1, OUTPUT); //declare all the buttons as inputs
  digitalWrite(butt1, HIGH); // set the inernal pull up resistor.
  pinMode(butt2, OUTPUT); //declare all the buttons as inputs
  digitalWrite(butt2, HIGH); // set the inernal pull up resistor.
  for (int i = 1;i<7;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but effications
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
  total1 = 0;
  total2 = 0;
  mode = 0;
  for ( j = 0;j<10;j++){
    total1 = total1 + abs(stepTime1[j]-stepTime1[j-1]);
    total2 = total2 + abs(stepTime2[j]-stepTime2[j-1]);
  if (abs(stepTime1[j]-stepTime2[j])<30){
    mode--;}
    else if stepTime1 > stepTime2{
    mode+2}
    }
    else if stepTime2 > stepTime1{
    mode++}
    }
  }
}

void step(){
  j++;
  if j > numSteps{ 
    j=1;
    stepTime1[0] = pulseIn(butt1,HIGH,60000);
    stepTime2[0] = pulseIn(butt2,HIGH,60000);
  }  
  stepTime1[j] = pulseIn(butt1,HIGH,60000);
  stepTime2[j] = pulseIn(butt2,HIGH,60000);
  if (((stepTime1[j]-stepTime1[j-1])=0)&&((stepTime2[j]-stepTime2[j-1])=0)){
j--;
  }
  if ((stepTime1[j]>stepTime1[j-1])&&(stepTime2[j]>stepTime2[j-1])){
j--;
stepTime1[j-1]=stepTime1[j];
stepTime2[j-1]=stepTime2[j];
  }
}


















