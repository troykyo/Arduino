int maxLevels = 10;
int maxCycles = 2000;
int pause = 1000;
int thisPin = 1;

int r[] = { 
  -1,   10, 2, 13, A0, A5, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int g[]= { 
  -1, 8,0,11,A2,A3, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int b[] = { 
  -1,   9, 1,12,A1,A4, -1 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int button[] = {
  -1, 3,4,5,6,7}; //Buttons

int rL[6];
int gL[6];
int bL[6];
int rD[6];
int gD[6];
int bD[6];
int rC[6];
int gC[6];
int bC[6];
int buttonState[6];
int buttonMode[6];
void setup(){
  Serial.begin(9600);
  for (thisPin = 1; thisPin < 6; thisPin++)  {//output
    pinMode(r[thisPin], OUTPUT);
    pinMode(g[thisPin], OUTPUT);
    pinMode(b[thisPin], OUTPUT);
    pinMode(button[thisPin], INPUT);
    digitalWrite (r[thisPin],  HIGH);
    digitalWrite (g[thisPin],  HIGH);
    digitalWrite (b[thisPin],  HIGH);
    buttonMode[thisPin]=1;
    delay (100); 
  }
}
void loop(){
  for (thisPin = 1; thisPin < 6; thisPin++)  {//test the buttons
    buttonState[thisPin]=digitalRead(button[thisPin]);//Read a button
    if (buttonState[thisPin] == HIGH){//is the button pressed?
      buttonMode[thisPin]++;//change Mode
      if (buttonMode[thisPin]>=6){//is the mode too high
        buttonMode[thisPin]=1;//reset the mode
      }
    }
    if (buttonMode[thisPin]=1){//mode 1
      Red();
    }
    if (buttonMode[thisPin]=2){//mode 1
      Green();
    }
    if (buttonMode[thisPin]=3){//mode 1
      Blue();
    }
    if (buttonMode[thisPin]=4){//mode 1
      Red();
      Blue();
    }
    if (buttonMode[thisPin]=5){//mode 1
      Red();
      Green();
    }
  }
    Serial.print(buttonMode[thisPin]);
      Serial.print(" ");

  delay (5);
  Off();
}  

void Red(){
  Serial.print("RED ");
  digitalWrite (r[thisPin],  HIGH);
  //Serial.print(r[thisPin]);    
  Serial.print(" ");
  //delay (pause);
  // digitalWrite (r[thisPin],  LOW);
}

void Green(){  
  Serial.print("GREEN ");
  digitalWrite (g[thisPin],  HIGH);
  //Serial.print(g[thisPin]);    
  Serial.print(" ");
  //delay (pause);
  //digitalWrite (g[thisPin],  LOW);
}

void Blue(){  
  Serial.print("BLU ");
  digitalWrite (b[thisPin],  HIGH);
  //Serial.print(b[thisPin]);    
  Serial.print(" ");
  //delay (pause);
  //digitalWrite (b[thisPin],  LOW);
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































