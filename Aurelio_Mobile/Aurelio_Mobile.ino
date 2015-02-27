
const int led[] = {
  -1,2,3,4,10,11,12};// PWM Pins that the LEDs are attached too.
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
    fadeTime[i] = random(400,2000);
    //fadeTime[i] = 1000;
    startTime[i] = 500*i;
    masterStartTime = millis(); //Time the sequesnce started 
  }
  currentTime = millis(); //What time is it right now 
}

void loop(){
  currentTime = millis(); //What time is it right now 
  for (int time = 0;time < 11;time++){
    for (int i = 1;i<7;i++){
      if (abs(currentTime-startTime[i])>fadeTime[i]){
        fadeTime[i] = random(400,2000);
      }
      if ((abs(currentTime-startTime[i]))<(fadeTime[i]/2)) {//fade up for half of the fade time
        currentTime = millis(); //What time is it right now 
        fadeLevel = map((currentTime-startTime[i]),0,(fadeTime[i]/2),0,10);
        if (fadeLevel>=time){
          digitalWrite(led[i], HIGH); 
        }
        else{
          digitalWrite(led[i], LOW); 
        }
      }
    }
  }
}







void RandomBlink(){
  for (int i = 1;i<7;i++){
    maxfade = random(0,2);
    digitalWrite(led[i], maxfade);
    Serial.print(i);
    Serial.print("-");
    Serial.print(maxfade);
    Serial.print(" ");
  }
  Serial.println(millis());
  delay(random(100,500));


}

void inOrder(){
  for (int i = 1;i<7;i++){
    digitalWrite(led[i], HIGH);
    delay(random(100,500));
  }
  for (int i = 1;i<7;i++){
    digitalWrite(led[i], LOW);
    delay(random(100,500));
  }
}

void old(){
  digitalWrite (13,HIGH);

  for (int i = 1;i<7;i++){
    if (((currentTime-masterStartTime) < (fadeTime[i])) && ((currentTime - masterStartTime - startTime[i]) > 0))  {//fade up for half of the fade time
      currentTime = millis(); //What time is it right now 
      digitalWrite(led[i], HIGH);
      currentTime = millis(); //What time is it right now   
    } 
    else{
      digitalWrite(led[i], LOW);

    }
  }
  currentTime = millis(); //What time is it right now 
  if ((currentTime - masterStartTime)>5000 ){
    masterStartTime = millis(); //Time the right now
    currentTime = millis(); //What time is it right now 
  }
  Serial.println("*");
}






















