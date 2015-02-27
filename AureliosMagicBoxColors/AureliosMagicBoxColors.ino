int maxLevels = 1;
int buttons[] = { 
  -1,   3, 4, 6, 5, 7, -1 };     // 
int buttonState[6];
int previousState[6]= { 
  -1,   0,0,0,0,0
};  

int r[] = { 
  -1,   10, 2, 13, A2, A5, -1
};     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int g[]= { 
  -1,   9, 1,12,A1,A4, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int b[] = { 
  -1, 8,0,11,A0,A3, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int rgb[3][7] = {//[whichRGB][whichButton]
  { 
    -1,   10, 2, 13, A2, A5, -1                            }
  ,
  { 
    -1,    9, 1, 12, A1, A4, -1                            }
  ,
  {
    -1,    8, 0, 11, A0, A3, -1                            }
};

int rgb16[3][7] = {//16 color definitions
  { 
    -1,   255,    0,  0,   255, 0, -1                            }
  ,
  { 
    -1,     0,  255,  0,  255, 255, -1                            }
  ,
  {
    -1,     0,    0, 255,   0,  255, -1                            }
};
int rgbC[3][6];//rgb Color
int rgbD[3][6];//rgb Destination
int rgbL[3][6];//rgb Luminance
int colors[6];

int thisPin = 6; 
unsigned int time = 0;
unsigned int startTime = 0;
unsigned int buttonTime = 0;


void setup(){
  Serial.begin(9600);
  for (thisPin = 1; thisPin < 6; thisPin++)  {//output
    pinMode(r[thisPin], OUTPUT);
    pinMode(g[thisPin], OUTPUT);
    pinMode(b[thisPin], OUTPUT);
    pinMode(buttons[thisPin], INPUT);
    digitalWrite (buttons[thisPin],  HIGH);
    digitalWrite (r[thisPin],  HIGH);
    digitalWrite (g[thisPin],  HIGH);
    digitalWrite (b[thisPin],  HIGH);

    delay (100); 
  }
  for (thisPin = 1; thisPin < 6; thisPin++)  {//output
    delay (100); 
    digitalWrite (r[thisPin],  LOW);
    digitalWrite (g[thisPin],  LOW);
    digitalWrite (b[thisPin],  LOW);
    colors[thisPin] = 1;
  }
}
void loop(){

  buttonCheck();
  drawColors();


}

void buttonCheck(){
  for (thisPin = 1; thisPin <= 5; thisPin++)  {//output
    buttonState[thisPin] = digitalRead(buttons[thisPin]);
    if (buttonState[thisPin] == LOW){
      if (previousState == 0){
        previousState = 1;
      colors[thisPin]++;
      if (colors[thisPin]>5){
        colors[thisPin] = 1;
      }  
    }
    }
    else if (buttonState[thisPin] == HIGH){
    previousState = 0;

    }

   Serial.print (colors[thisPin]);
   //Serial.print (buttonState[thisPin]);

   Serial.print ("\t");
  }
     Serial.println ("\t");

}

void calculateColors(){
  for (int whichRGB = 1; whichRGB <= 3; whichRGB++)  {//output

    for (int whichButton = 1; whichButton < 6; whichButton++)  {//output
      rgbC[whichRGB][whichButton] = map(rgb16[whichRGB][whichButton],0,255,0,maxLevels-1);
    }
  }
}

void drawColors(){

  for (thisPin = 1; thisPin <= 5; thisPin++)  {//output

    if (colors[thisPin] == 1){//RED
      digitalWrite (rgb[1][thisPin],HIGH);
      digitalWrite (rgb[2][thisPin],LOW);
      digitalWrite (rgb[2][thisPin],LOW);
    }
    if (colors[thisPin] == 2){//GREEN
      digitalWrite (rgb[1][thisPin],LOW);
      digitalWrite (rgb[2][thisPin],HIGH);
      digitalWrite (rgb[2][thisPin],LOW);
    }
    if (colors[thisPin] == 3){//BLUE
      digitalWrite (rgb[1][thisPin],LOW);
      digitalWrite (rgb[2][thisPin],LOW);
      digitalWrite (rgb[2][thisPin],HIGH);
    }
    if (colors[thisPin] == 4){//ORANGE
      digitalWrite (rgb[1][thisPin],HIGH);
      digitalWrite (rgb[2][thisPin],HIGH);
      digitalWrite (rgb[2][thisPin],LOW);
    }
    if (colors[thisPin] == 5){//Violet
      digitalWrite (rgb[1][thisPin],HIGH);
      digitalWrite (rgb[2][thisPin],LOW);
      digitalWrite (rgb[2][thisPin],HIGH);
    }
  }
}





























