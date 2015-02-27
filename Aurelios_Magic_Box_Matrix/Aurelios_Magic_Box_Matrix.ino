int maxLevels = 1;
int buttons[] = { 
  -1,   3, 4, 6, 5, 7, -1 };     // 
int buttonState[6];

int r[] = { 
  -1,   10, 2, 13, A2, A5, -1
};     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int g[]= { 
  -1,   9, 1,12,A1,A4, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int b[] = { 
  -1, 8,0,11,A0,A3, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int rgb[3][7] = {//[whichRGB][whichButton]
  { 
    -1,   10, 2, 13, A2, A5, -1              }
  ,
  { 
    -1,    9, 1, 12, A1, A4, -1              }
  ,
  {
    -1,    8, 0, 11, A0, A3, -1              }
};

int rgb16[3][7] = {//16 color definitions
  { 
    -1,   255,    0,  0,   255, 0, -1              }
  ,
  { 
    -1,     0,  255,  0,  255, 255, -1              }
  ,
  {
    -1,     0,    0, 255,   0,  255, -1              }
};
int rgbC[3][6];//rgb Color
int rgbD[3][6];//rgb Destination
int rgbL[3][6];//rgb Luminance

int thisPin = 6; 
unsigned int time = 0;
unsigned int startTime = 0;

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

  }
}
void loop(){

  Serial.println (maxLevels);
  startTime = millis();
  while ((startTime-time)<100){
  time =millis();
  calculateColors();
  drawColors();
  }

}

void calculateColors(){
  for (int whichRGB = 1; whichRGB <= 3; whichRGB++)  {//output

    for (int whichButton = 1; whichButton < 6; whichButton++)  {//output
      rgbC[whichRGB][whichButton] = map(rgb16[whichRGB][whichButton],0,255,0,maxLevels-1);
    }
  }
}

void drawColors(){

  for (int x = 1; x <= maxLevels; x++)  {//output

    //Red
    for (int whichButton = 1; whichButton < 6; whichButton++)  {//output
      if (rgbC[1][whichButton]>=x){
        digitalWrite (rgb[1][whichButton],  HIGH);
      }
      else{     
        digitalWrite (rgb[1][whichButton],   LOW);
      }
      Serial.print(rgbC[1][whichButton]);
      Serial.print(" ");
      Serial.print(rgb16[1][whichButton]);
      Serial.print("\t");
    }
    Serial.println ("\tRED");

    //Green
    for (int whichButton = 1; whichButton < 6; whichButton++)  {//output
      if (rgbC[2][whichButton]<x){
        digitalWrite (rgb[2][whichButton],  HIGH);
      }
      else{     
        digitalWrite (rgb[2][whichButton],   LOW);
      }
      Serial.print(rgbC[2][whichButton]);
      Serial.print(" ");
      Serial.print(rgb16[2][whichButton]);
      Serial.print("\t");
    }
    Serial.println ("\tGREEN");

    //Blue
    for (int whichButton = 1; whichButton < 6; whichButton++)  {//output
      if (rgbC[3][whichButton]>=x){
        digitalWrite (rgb[3][whichButton],  HIGH);
      }
      else{     
        digitalWrite (rgb[3][whichButton],   LOW);
      }
      Serial.print(rgbC[1][whichButton]);
      Serial.print(" ");
      Serial.print(rgb16[1][whichButton]);
      Serial.print("\t");
    }
    Serial.println ("\tBLUE");
  }
  Serial.println ();

}






















