


const unsigned int sensibilita = 100;
const unsigned int pause = 400;
const int readings = 3;

int cuore[] = { 

  -1,  2, 3, 4, 5, 6,  7,46,44, 8, 9, 45,10,11,12,13, 42 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)

// -1, 31,32,33,34,35, 38,42,44,37,39, 45,40,36,41,43, 46 };

int mic[] = { 
  -1, A1, A2, A3, A4, A5, A6, A7};       // an array of analog input pins numbers to which the colororganic spectralized is attached
int micGND[] = {
  -1, 62, 63, 64, 65, 66, 67, 68};       // an array of analog input pins numbers to which the colororganic spectralized is at
int spectraPower = 53;  

const int questoCuore [20][8] = {//seperate atrrays for semingly random blinking
  {
    0, 4, 9, 7, 12, 13, 10, 8                                                        }
  ,
  {
    0, 15, 3, 14, 1, 10, 13, 2                                                        }
  ,
  {
    0, 7, 1, 5, 8, 13, 15, 2                                                        }
  ,
  {
    0,  13, 11, 3, 2, 8, 6, 10                                                        }
  ,
  {
    0, 3, 10, 14, 12, 1, 9, 11                                                        }
  ,
  {
    0, 5, 7, 15, 6, 11, 4, 13                                                        }
  ,
  {
    0, 7, 6, 10, 8, 15, 3, 2                                                        }
  ,
  {
    0,  5, 8, 10, 1, 4, 9, 6                                                        }
  ,
  {
    0,  4, 7, 2, 5, 14, 11, 6                                                        }
  ,
  {
    0, 6, 8, 4, 5, 10, 1, 9                                                        }
  ,
  {
    0,  10, 2, 1, 4, 8, 12, 7                                                        }
  ,
  {
    0, 14, 5, 11, 10, 4, 1, 9                                                        }
  ,
  {
    0, 10, 11, 9, 3, 5, 15, 1                                                        }
  ,

  {
    0,  5, 13, 14, 3, 10, 2, 9                                                        }
  ,
  {
    0,  9, 14, 3, 2, 4, 5, 1                                                        }
  ,
  {
    0,  9, 5, 7, 12, 8, 2, 13                                                        }
  ,
  {
    0,  12, 11, 3, 6, 2, 1, 9                                                        }
  ,
  {
    0, 4, 6, 14, 15, 11, 10, 8                                                        }
  ,
  {
    0, 1, 5, 10, 2, 13, 12, 11                                                        }
  ,
  {
    0, 2, 7, 9, 8, 11, 15, 14                     }
};
int sogliaFreq[] = {//the baseline for sound
  -1, 800, 800, 800, 800, 800, 800, 800};
int sogliaMax[] = {//the Max volume recieved
  -1, 0, 0, 0, 0, 0, 0, 0};
int sogliaAccende[] = {//how much difference is needed to illuminate the heart
  -1, 10, 10, 10, 10, 10, 10, 10};

unsigned int freq[8][readings];
unsigned int average[8];
unsigned int qualeVoce = 1;
unsigned int silence = 0;
unsigned int confirmSilence = 0;
unsigned int silenceBegins = 0;
unsigned long counter = 0;
unsigned int light = 0;
int bright = 128;
unsigned int recalibrate1 = 0;
unsigned int recalibrate2 = 0;


void setup(){
  Serial.begin(9600);
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  pinMode(spectraPower, OUTPUT);
  digitalWrite (spectraPower,  LOW);

  for (int thisPin = 1; thisPin < 16; thisPin++)  {//output
    pinMode(cuore[thisPin], OUTPUT);
    digitalWrite (cuore[thisPin],  HIGH);
  }
  for (int thisPin = 1; thisPin < 8; thisPin++)  {//input
    pinMode(mic[thisPin], INPUT);
    digitalWrite (mic[thisPin], HIGH);
    pinMode(micGND[thisPin], OUTPUT);
    digitalWrite (micGND[thisPin], LOW);
  }


  //qualeVoce = random(0,19);
  recalibrate();//checks the current readings and recalibrates

  delay (500);//blink the cuori for half a second (boot test)

  for (int thisPin = 1; thisPin < 16; thisPin++)  {
    digitalWrite (cuore[thisPin], LOW);   
  }

  Serial.println("setup complete");

}

void loop() {
  counter++;
  Serial.println (counter);
  Serial.println ("\t");
  if (counter > 32000){
    deepRecalibrate();
    counter = 0;
  }
  if (counter%100 == 0){
    recalibrate();
  }

  for (int j = 0; j < readings; j++)  { 
    for (int k = 1; k < 8; k++)  { 
      freq[j][k] = analogRead(mic[k]);
      average[k] = average[k] + freq[j][k];

      if (freq[j][k] > (sogliaFreq[k]+sogliaAccende[k])){
        confirmSilence = 0;
        silence--;
        if (silence <= 0) {
          silence = 1;
        }
      }
      else {
        silenceBegins = silenceBegins + 1;
        confirmSilence = 1;
      }
    } 
    if (silenceBegins > 7){
      silence++;
      silenceBegins = 0;
    }
  }
  for (int k = 1; k < 8; k++)  { 
    average[k] = average[k]/(readings);
    Serial.print(average[k]);
    light = questoCuore[qualeVoce][k];
    Serial.print ("\t");
    Serial.print(light);
    Serial.print ("\t");
    if (average[k] > sogliaMax[k]){//Reset the max threshold if a larger value than the max is seen
      sogliaMax[k] = average[k];
      Serial.print ("^");
    }

    if (average[k] > (sogliaFreq[k]+sogliaAccende[k])){
      bright = map(average[k],sogliaFreq[k]+sogliaAccende[k],sogliaMax[k],30,255);
      light = questoCuore[qualeVoce][k];
      analogWrite (cuore[light], bright);
    }
    else {
      light = questoCuore[qualeVoce][k];
      analogWrite (cuore[light], 0);
      Serial.print ("\t");
    }
    delay (1);
  }

  Serial.println (silence);

  if (silence > pause){
    if (confirmSilence == 0){
      digitalWrite (spectraPower, HIGH);

      confirmSilence = 1;
      qualeVoce++;
      Serial.println ("Prossimi Cuori");
      silence = 0;
      if (qualeVoce > 20){
        qualeVoce = 0;
      }
      for (int k = 1; k < 16; k++)  { 
        analogWrite (cuore[k], 0);  
      } 
      digitalWrite (spectraPower, LOW);
    }
  }
}


void recalibrate(){
  Serial.println ("Recalibrating");
  for (int j = 0; j < readings; j++)  { // recalibrate the ambient noise 
    for (int k = 1; k < 8; k++)  { 
      freq[j][k] = analogRead(mic[k]);
      average[k] = average[k] + freq[j][k];
    } 
  }
        digitalWrite (spectraPower, HIGH);

  for (int k = 1; k < 8; k++)  { 
    analogWrite (cuore[k], 0);//reset the lights.

    average[k] = average[k]/(readings-1);

    if (average[k] < sogliaFreq[k]){
      sogliaFreq[k] = average[k];
      Serial.print ("v");
    }
    sogliaAccende[k] = (abs(sogliaMax[k]-sogliaFreq[k]))/sensibilita; //ADGIUSTAMI QUI!!!!!
    Serial.print(average[k]);
    Serial.print ("\t");
    Serial.print(sogliaAccende[k]);
    Serial.print ("\t");

  }
          digitalWrite (spectraPower, LOW
          );

  Serial.println ();

}

void deepRecalibrate(){
  Serial.println ("Deep Recalibrating");
asm volatile ("  jmp 0");
  }  























