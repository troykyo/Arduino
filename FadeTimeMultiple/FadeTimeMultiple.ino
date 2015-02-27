

const int led[] = {
  -1,3,9,10,11};// PWM Pins that the LEDs are attached too.
int fadeLevel;       //level for fading 
int fadeTime[] = {
  -1,0,0,0,0,0,0}; //Time for a fade in Milliseconds
unsigned long startTime[] = {
  -1,0,0,0,0,0,0};    // the  time the interaction started
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
const int maxLed = 4;

void setup() {  
  digitalWrite (2,LOW);
  digitalWrite (8,LOW);
  digitalWrite (4,LOW); 
  digitalWrite (12,LOW);
  pinMode(13, OUTPUT);  
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
  for (int i = 1;i<=maxLed;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but efficatios
    fadeTime[i] = random(1000,10000);// An array for choosing a random array time.
    startTime[i] = millis(); //An Array to save what time the fade started for each LED
  }
  currentTime = millis(); //What time is it right now 
}

void loop(){
  digitalWrite (13,HIGH);//blink the onboard LED for feedback
  for (int i = 1;i<7;i++){//scroll through our 6 leds
    if ((abs(currentTime-startTime[i]))<(fadeTime[i]/2)) {//fade up for half of the fade time by checking what time is it
      currentTime = millis(); //What time is it right now 
      fadeLevel = map((currentTime-startTime[i]),0,(fadeTime[i]/2),0,255);//Set the fade intensity based upon time 
      // Serial.print((currentTime-startTime[i]));
      //Serial.print(" ");
      analogWrite(led[i], fadeLevel); //Fade the current LED to the correct intensity. 
    }
    if ((abs(currentTime-startTime[i]))<(fadeTime[i])&&(abs(currentTime-startTime[i]))>(fadeTime[i]/2))  {//fade down for half of the fade time
      currentTime = millis(); //What time is it right now 
      fadeLevel = map((currentTime-startTime[i]),(fadeTime[i]/2),fadeTime[i],0,255);
      //Serial.print((currentTime-startTime[i]));
      //Serial.print(" ");
      analogWrite(led[i], (255-fadeLevel)); //Fade the current LED to the correct intensity.
      digitalWrite (13,LOW);
    }
    if ((abs(currentTime-startTime[i]))>(fadeTime[i])) {//If the fade has completed, select a new fade time.
      fadeTime[i] = random(1000,10000);  
      startTime[i] = millis(); //Time the 
      currentTime = millis(); //What time is it right now 
      Serial.print(" ");
      Serial.print(fadeTime[i]);
    }
  }
}








