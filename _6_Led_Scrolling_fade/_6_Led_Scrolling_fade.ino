

const int led[] = {
  -1,3,5,6,9,10,11};// PWM Pins that the LEDs are attached too.
int fadeLevel;       //counter for fading 
long fadeTime[] = {
  -1,0,0,0,0,0,0}; //Time for a fade in Milliseconds
long startTime[] = {
  -1,0,50,100,150,200,250};    // the  time the interaction started

unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long syncTime = 0;    // the  time the interaction started
int maxfade = 128 ;
long masterStartTime = 0;

void setup() {  

  pinMode(13, OUTPUT);  
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
  for (int i = 1;i<7;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but effications
    //fadeTime[i] = random(1000,10000);
    fadeTime[i] = 1000;
    startTime[i] = 50*i;
    masterStartTime = millis(); //Time the fade started 
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












