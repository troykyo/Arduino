int led = 11;

int fadeTime = 5000; //Time for a fade in Milliseconds
int fadeLevel;       //counter for fading 

unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time the interaction started

void setup() {  
  pinMode(led, OUTPUT);  // declare the led as OUTPUT:
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
}

void loop(){
  fadeTime = random(1000,10000);
  startTime = millis(); //Time the 
  currentTime = millis(); //What time is it right now 
  digitalWrite (13,HIGH);
  while ((abs(currentTime-startTime))<(fadeTime/2)) {//fade up for half of the fade time
    currentTime = millis(); //What time is it right now 
    fadeLevel = map((currentTime-startTime),0,(fadeTime/2),0,255);
    Serial.print((currentTime-startTime));
    Serial.print(" ");
    analogWrite(led, fadeLevel); 
  }
  while ((abs(currentTime-startTime))<(fadeTime)) {//fade down for half of the fade time
    currentTime = millis(); //What time is it right now 
    fadeLevel = map((currentTime-startTime),(fadeTime/2),fadeTime,255,0);
    Serial.print((currentTime-startTime));
    Serial.print(" ");
    analogWrite(led, fadeLevel); 
    digitalWrite (13,LOW);
  }

}



