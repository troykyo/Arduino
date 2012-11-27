int fadeTime = 0; //Time for a fade in Milliseconds
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time the interaction starte
int brightness = 0;
int randomD = 0;

void setup() {  
  pinMode(11, OUTPUT);  // declare the leftStrap as OUTPUT:
  pinMode(9, OUTPUT);  // declare the rightStrap as OUTPUT:
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:

}


void loop(){
  randomD = random(1,4);
  Serial.print(" ");
  Serial.println(randomD);
  analogWrite(11, 0); 
  analogWrite(9, 0); 
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
        if ((randomD == 1)){
          analogWrite(11, brightness); 
          analogWrite(9, (255-abs(brightness*2-255))); 
        }
        if ((randomD == 2)){
          analogWrite(9, (255-abs(brightness*2-255))); 
          analogWrite(11, (255-abs(brightness*2-255))); 
        }  
        if ((randomD == 3)){
          analogWrite(9, brightness); 
          analogWrite(11, brightness);   
        } 
      }
    }
    if (i>5){ 
      Serial.print(i);
      while ((abs(currentTime-startTime))<(fadeTime/2)) {//do this for half of the fade time
        digitalWrite (13,HIGH);
        currentTime = millis(); //What time is it right now 
        brightness = map((currentTime-startTime),0,fadeTime/2,0,255);
        if ((randomD == 1)){
          analogWrite(11, brightness); 
          analogWrite(9, (255-abs(brightness*2-255))); 
        }
        if ((randomD == 2)){
          analogWrite(9, brightness);
          analogWrite(11, (255-abs(brightness*2-255))); 
        }  
        if ((randomD == 3)){
          analogWrite(9, brightness); 
          analogWrite(11, brightness);   
        } 
      }
    }
  }
}










