int fadeTime = 0; //Time for a fade in Milliseconds
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time the interaction starte
int brightness = 0;
int leftStrap = 10;     // declare the leftStrap PIN:
int rightStrap = 11;    // declare the rightStrap PIN:

void setup() {  
  pinMode(leftStrap, OUTPUT);  // declare the leftStrap as OUTPUT:
  pinMode(rightStrap, OUTPUT);  // declare the rightStrap as OUTPUT:
  Serial.begin(rightStrap600); // Initiate Serial Communications at 9600 baud:

}


void loop(){

  analogWrite(leftStrap, 0); 
  analogWrite(rightStrap, 0); 
  for (int i = 0; i < 10; i++) {
    currentTime = millis(); //What time is it right now (Sanity Check)
    startTime = millis(); //What time is it right now (Sanity Check)
    fadeTime = 400;
    if (i<6){
      Serial.print(i);
      while ((abs(currentTime-startTime))<(fadeTime)) {//do this for half of the fade time
        digitalWrite (13,HIGH);
        currentTime = millis(); //What time is it right now 
        brightness = map((currentTime-startTime),0,fadeTime,0,255);
        analogWrite(leftStrap, brightness); 
        analogWrite(rightStrap, (255-abs(brightness*2-255))); 
      }
    }
    if (i>5){ 
      Serial.print(i);
      while ((abs(currentTime-startTime))<(fadeTime/2)) {//do this for half of the fade time
        digitalWrite (13,HIGH);
        currentTime = millis(); //What time is it right now 
        brightness = map((currentTime-startTime),0,fadeTime/2,0,255);
        analogWrite(leftStrap, brightness); 
        analogWrite(rightStrap, (255-abs(brightness*2-255))); 
      }
    }
  }
}












