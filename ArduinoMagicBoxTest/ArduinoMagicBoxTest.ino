int maxLevels = 10;
int maxCycles = 1000;
int lights[] = { 

  -1,   8, 9,10, 0, 1, 2, 11,12,13 ,A0,A1,A2, A3,A4,A5, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)

int r[] = { 
  -1,   10, 2, 13, A2, A5, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int g[]= { 
  -1,   9, 1,12,A1,A4, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int b[] = { 
  -1, 8,0,11,A0,A3, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
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
  for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    pinMode(r[thisPin], OUTPUT);
    pinMode(g[thisPin], OUTPUT);
    pinMode(b[thisPin], OUTPUT);
    digitalWrite (r[thisPin],  HIGH);
    digitalWrite (g[thisPin],  HIGH);
    digitalWrite (b[thisPin],  HIGH);

    delay (100); 
  }
  for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (lights[thisPin],  LOW);
    delay (100); 
    digitalWrite (r[thisPin],  LOW);
    digitalWrite (g[thisPin],  LOW);
    digitalWrite (b[thisPin],  LOW);
    rL[thisPin] = 0;
    gL[thisPin] = 0;
    bL[thisPin] = 0;

    rD[thisPin] = maxLevels;
    gD[thisPin] = maxLevels;
    bD[thisPin] = maxLevels;

  }
}
void loop(){

  for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (r[thisPin],  HIGH);
    Serial.print("RED ");
  } 
  delay(1000);
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (g[thisPin],  HIGH);
    Serial.print("GREEN ");
  } 
    delay(1000);
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (b[thisPin],  HIGH);
    Serial.print("BLUE ");
  } 
    delay(1000);
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (r[thisPin],  LOW);
    digitalWrite (g[thisPin],  LOW);
    digitalWrite (b[thisPin],  LOW);
    Serial.println("Reset ");
  }
   delay(1000);
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (g[thisPin],  HIGH);
    Serial.print("GREEN ");
  } 
    delay(1000);
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (b[thisPin],  HIGH);
    Serial.print("BLUE ");
  } 
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (r[thisPin],  HIGH);
    Serial.print("RED ");
  } 
      delay(1000);
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (r[thisPin],  LOW);
    digitalWrite (g[thisPin],  LOW);
    digitalWrite (b[thisPin],  LOW);
    Serial.println("Reset ");
  }
  

  delay(1000);
  
    delay(1000);
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (b[thisPin],  HIGH);
    Serial.print("BLUE ");
  }
      delay(1000);

     for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (r[thisPin],  HIGH);
    Serial.print("RED ");
  }  
     delay(1000);

   for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (g[thisPin],  HIGH);
    Serial.print("GREEN ");
  } 
    delay(1000);
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    digitalWrite (r[thisPin],  LOW);
    digitalWrite (g[thisPin],  LOW);
    digitalWrite (b[thisPin],  LOW);
    Serial.println("Reset ");
  }
}















