int maxLevels = 10;
int maxCycles = 2000;
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
    rL[thisPin] = random(0,maxLevels);
    gL[thisPin] = random(0,maxLevels);
    bL[thisPin] = random(0,maxLevels);

    rD[thisPin] = random(0,maxLevels);
    gD[thisPin] = random(0,maxLevels);
    bD[thisPin] = random(0,maxLevels);

  }
}
void loop(){

  for (int i = 1; i <= maxCycles; i++)  {//output
    for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
      rC[thisPin] = map(i,0,maxCycles, rL[thisPin] , rD[thisPin]); 
      gC[thisPin] = map(i,0,maxCycles, gL[thisPin] , gD[thisPin]); 
      bC[thisPin] = map(i,0,maxCycles, bL[thisPin] , bD[thisPin]); 
      Serial.print (rC[thisPin]) ; 
      Serial.print (" ") ; 
      Serial.print (gC[thisPin]) ; 
      Serial.print (" ") ; 
      Serial.print (bC[thisPin]) ; 
      Serial.print ("\t") ;     
   }
   
    Serial.println (" ") ;     

    for (int x = 1; x <= maxLevels; x++)  {//output
      if (rC[x]>=x){
        digitalWrite (r[x],  HIGH);
      }
      else{     
        digitalWrite (r[x],  LOW);
      }
      if (gC[x]>=x){
        digitalWrite (g[x],  HIGH);
      }
      else{     
        digitalWrite (g[x],  LOW);
      }
      if (bC[x]>=x){
        digitalWrite (b[x],  HIGH);
      }
      else{     
        digitalWrite (b[x],  LOW);
      }
    }
  }
  for (int thisPin = 1; thisPin < 6; thisPin++)  {//output
    rL[thisPin] = rD[thisPin];
    gL[thisPin] = gD[thisPin];
    bL[thisPin] = bD[thisPin];

    rD[thisPin] = random(0,maxLevels);
    gD[thisPin] = random(0,maxLevels);
    bD[thisPin] = random(0,maxLevels);
  }
}













