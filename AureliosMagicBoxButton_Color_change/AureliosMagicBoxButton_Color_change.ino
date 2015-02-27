int buttons[] = { 
  -1,   3, 4, 6, 5, 7, -1 };     // 
int buttonState[6];

int r[] = { 
  -1,   10, 2, 13, A2, A5, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int g[]= { 
  -1,   9, 1,12,A1,A4, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int b[] = { 
  -1, 8,0,11,A0,A3, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int rgb[6][6][6][6];
int rL[6];
int gL[6];
int bL[6];
int rD[6];
int gD[6];
int bD[6];
int rC[6];
int gC[6];
int bC[6];
int thisPin = 6; 

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

    for (thisPin = 1; thisPin < 6; thisPin++)  {//output
      //buttonPressed();
       buttonState[thisPin] = digitalRead(buttons[thisPin]);
  if (buttonState[thisPin] == HIGH){
   digitalWrite ( r[thisPin],LOW);
   //digitalWrite ( g[thisPin],LOW);
   digitalWrite ( b[thisPin],LOW);
   
  }
  else {
   digitalWrite ( r[thisPin],HIGH);
   digitalWrite ( g[thisPin],HIGH);
   digitalWrite ( b[thisPin],HIGH);

  }
}
}
  
 











