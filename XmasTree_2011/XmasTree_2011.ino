;

const int led[] = {
  -1,12,5,6,9,10,11};// PWM Pins that the LEDs are attached too.
int fadeLevel;       //counter for fading 
int fadeTime[] = {
  -1,0,0,0,0,0,0}; //Time for a fade in Milliseconds
int i = 0; //counter
unsigned long startTime[] = {
  -1,0,0,0,0,0,0};    // the  time the interaction started

unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long syncTime = 0;    // the  time the interaction started


void setup() {  

  pinMode(13, OUTPUT); 
  digitalWrite (13,HIGH); 
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
  for (int i = 1;i<7;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesary, but effications
    fadeTime[i] = random(1000,10000);
    startTime[i] = millis(); //Time the 
    Serial.print(i);
    Serial.print(" ");
    Serial.print(fadeTime[i]);
    Serial.print(" ");
  }
  currentTime = millis(); //What time is it right now 
}

void loop(){
  for (int i = 1;i<7;i++){
  if ((currentTime-startTime[i])<(fadeTime[i])) {
    currentTime = millis(); //What time is it right now 
    fadeLevel = random(127,255);
    // Serial.print((currentTime-startTime[i]));
    //Serial.print(" ");
    analogWrite(led[i], fadeLevel); 
    delay((random(5,20)));
  }
  if ((abs(currentTime-startTime[i]))>(fadeTime[i])) {
    fadeTime[i] = random(10,50);
    startTime[i] = millis(); //Time the 
    currentTime = millis(); //What time is it right now 
    Serial.print(" ");
    Serial.print(fadeTime[i]);
  }
}
}









