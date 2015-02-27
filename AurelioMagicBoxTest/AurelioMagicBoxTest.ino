int maxLevels = 10;
int maxCycles = 2000;
int pause = 1000;
int thisPin = 1
int lights[] = { 
  -1,   8, 9,10, 0, 1, 2, 11,12,13 ,A0,A1,A2, A3,A4,A5, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)

int r[] = { 
  -1,   10, 2, 13, A0, A5, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int g[]= { 
  -1, 8,0,11,A2,A3, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int b[] = { 
  -1,   9, 1,12,A1,A4, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)

int rL[6];
int gL[6];
int bL[6];
int rD[6];
int gD[6];
int bD[6];
int rC[6];
int gC[6];
int bC[6];

void setup(){
  Serial.begin(9600);
  for (thisPin = 1; thisPin < 6; thisPin++)  {//output
    pinMode(r[thisPin], OUTPUT);
    pinMode(g[thisPin], OUTPUT);
    pinMode(b[thisPin], OUTPUT);
    digitalWrite (r[thisPin],  HIGH);
    digitalWrite (g[thisPin],  HIGH);
    digitalWrite (b[thisPin],  HIGH);

    delay (100); 
  }
}
void loop(){
  Red();
  Off();
  Blue();
  Off();
  Green();
  Off();
  Red();
  Blue();
  Off();
  Red();
  Green();
  Off();
  Green();
  Blue();
  Off();
  Red();
  Blue();
  Green();
  Off();
}  
void Red(){
  Serial.print("RED ");
  for (thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (r[thisPin],  HIGH);
    //Serial.print(r[thisPin]);    
    Serial.print(" ");
    //delay (pause);
    // digitalWrite (r[thisPin],  LOW);
  }
}

void Green(){  
  Serial.print("GREEN ");
  for (thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (g[thisPin],  HIGH);
    //Serial.print(g[thisPin]);    
    Serial.print(" ");
    //delay (pause);
    //digitalWrite (g[thisPin],  LOW);
  }
}

void Blue(){  
  Serial.print("BLU ");
  for (thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (b[thisPin],  HIGH);
    //Serial.print(b[thisPin]);    
    Serial.print(" ");
    //delay (pause);
    //digitalWrite (b[thisPin],  LOW);
  }
}

void Off(){  
  Serial.println(" ");
  delay (pause);
  for (thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (r[thisPin],  LOW);
    digitalWrite (b[thisPin],  LOW);
    digitalWrite (g[thisPin],  LOW);
  }
}


























