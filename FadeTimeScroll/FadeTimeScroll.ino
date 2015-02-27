

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

  pinMode(13, OUTPUT);  
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
  for (int i = 1;i<=maxLed;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but efficatios
    fadeTime[i] = 1000;// An array for choosing a random array time.
    startTime[i] = millis(); //An Array to save what time the fade started for each LED
  }
  currentTime = millis(); //What time is it right now 
}

void loop(){
  digitalWrite (13,HIGH);//blink the onboard LED for feedback
  currentTime = millis(); //What time is it right now 
  for (int i=1;i<=maxLed;i++){//scroll through our leds
    int thisFade = abs(currentTime-startTime[i]);//how long into the fade are we
    int startFade = fadeTime[i]/maxLed/2*(i-1);//set the delay to make the fade scroll
    int endFade = fadetime[i] - (fadeTime[i]/maxLed/2*(maxLed-i));
    if ((thisFade>(startFade))&&(thisFade<(endFade/2)))  {//fade down for half of the fade time
      currentTime = millis(); //What time is it right now 
      fadeLevel = map(thisfade,startFade,endFade/2,0,255);//Set the fade intensity based upon time 
      // Serial.print((currentTime-startTime[i]));
      //Serial.print(" ");
      analogWrite(led[i], fadeLevel); //Fade the current LED to the correct intensity. 
    }
    else if (thisFade)<(fadeTime[i])&&(thisFade)>(startFade)  {//fade down for half of the fade time
      currentTime = millis(); //What time is it right now 
      fadeLevel =  map(thisfade,startFade+endFade/2,endFade,255,0);
      //Serial.print((currentTime-startTime[i]));
      //Serial.print(" ");
      analogWrite(led[i], (255-fadeLevel)); //Fade the current LED to the correct intensity.
      digitalWrite (13,LOW);
    }
    if (thisFade>(fadeTime[i])) {//If the fade has completed, select a new fade time.
      startTime[i] = millis(); //Reset the Start Time
      currentTime = millis(); //What time is it right now 
      Serial.print(i);
      Serial.print(" ");
      Serial.print(fadeTime[i]);
    }
  }
 Serial.println(); 
}









