int cuore[] = { 
  -1, 31,32,33,34,35, 38,42,44,37,39, 45,40,36,41,43, 46 };       // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
int mic[] = { 
  -1, A1, A2, A3, A4, A5, A6, A7};       // an array of analog input pins numbers to which the colororganic spectralized is attached
int micGND[] = {
  -1, 62, 63, 64, 65, 66, 67, 68};       // an array of analog input pins numbers to which the colororganic spectralized is at

// -1, A8, A9, A10, A11, A12, A13, A14};       // an array of analog input pins numbers to which the colororganic spectralized is at


unsigned int freq[8][8][8];
unsigned int average[8][8];
unsigned int sequenceStart = 0;
unsigned int sequenceStep = 0;

unsigned int x,y,z;
unsigned int qualeVoce[16];
unsigned int thisVoce = 1;
unsigned int nextVoce = 0;
unsigned int voce [8][8];
const int signatureMin = 50;
const int sogliaVoce = 400;

int thisCuore[16];

int silence = 0; //counter for if it was silent the pass before.
unsigned int silenceStart = 0; //Time the silence started
const int silenceDuration = 500;// milliseconds of silence needed between words to evaluate a new vocal signature.

void setup() {
  Serial.begin(9600);
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:

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

  Serial.print(millis());
  for (x = 0; x < 9; x++)  {//reset the array
    for (y = 0; y < 9; y++)  { 
      for ( z = 0; z < 9; z++)  { 
        freq[x][y][z]=500;
        average[z][x]=500;
        voce [x][y] = 300;
      }
    } 
  }
  Serial.print(" ");
  Serial.println(millis());

  delay (500);//blink the cuori for half a second (boot test)
  for (int thisPin = 1; thisPin < 16; thisPin++)  {
    digitalWrite (cuore[thisPin], LOW);   
  }
  thisCuore[0]=17;
  Serial.println("setup complete");
}

void loop() {
  listen();
  Serial.println("Loop Complete: Ding!");
}

void listen() {//x Average Average y average z individual reading
  sequenceStart = millis();
  x = 0;
  while (x < 9) {//reset the array
    sequenceStep = millis();
    x = abs((sequenceStart-sequenceStep)/2000);
    if (x == 0){
      x=1;
    }
    Serial.println(x);
    for (y = 1; y < 8; y++)  { 
      for (z = 1; z < 8; z++)  { 
        freq[x][y][z] = analogRead(mic[z]);
        average[x][z] = y*average[x][z]+freq[x][y][z]; //weight the past average and add the new reading
        if (y == 1) { // Average must be doubled the first time
          average[x][z] = average[x][z]+freq[x][y][z];
        }
        average[x][z] = average[x][z]/(y+1); // average the average

        Serial.print (x);
        Serial.print (",");
        Serial.print (y);
        Serial.print (",");
        Serial.print (z);
        Serial.print ("\t");
        Serial.print (freq[x][y][z]); //Serial the reading
        Serial.print ("\t");
        Serial.print (average[x][z]); 
        Serial.print ("\t");

      }
      Serial.println ();
      lightCuore();
    }
    signatureVoce();
  }
}

void lightCuore() {
  if (average[x][1] > sogliaVoce || average[x][2] > sogliaVoce || average[x][3] > sogliaVoce || average[x][4] > sogliaVoce || average[x][5] > sogliaVoce ||average[x][6] > sogliaVoce ||average[x][7] > sogliaVoce ||average[x][8] > sogliaVoce){
    /* for (int j = 1; j < 8; j++) { 
     Serial.print (x);
     Serial.print (",");
     Serial.print (y);
     Serial.print (",");
     Serial.print (j);
     Serial.print ("\t");
     Serial.print (average[x][j]);
     Serial.print ("\t"); 
     }*/
    digitalWrite  (cuore[thisVoce], HIGH );
    Serial.print ("Which Heart: ");
    Serial.print (thisVoce);
    Serial.print ("\t");
    Serial.println (" yes ");



    //Serial.print (cuore[qualeVoce[thisVoce]]) ;
    silence = 0;
  }
  else {
    digitalWrite  (cuore[thisVoce], LOW );
    if (silence == 0){
      silence = 1;
      }
      for (int j = 1; j < 8; j++) { 
        Serial.print (x);
        Serial.print (",");
        Serial.print (y);
        Serial.print (",");
        Serial.print (j);
        Serial.print ("\t");
        Serial.print (average[x][j] );
        Serial.print ("\t"); 
      Serial.println ("Silence\tNo");
      silenceStart = millis();
    }
  }
}

void reset() {
  Serial.println("reset");
  nextVoce = 0;
  for (int thisPin = 1; thisPin < 16; thisPin++)  {//output
    digitalWrite (cuore[thisPin], LOW);
    thisCuore[thisPin] = random(1,16);
  }
  for (int thisPin = 1; thisPin < 7; thisPin++)  {//reset the hearts for 6 voices
    thisCuore[thisPin] = random(1,16);
    for (int test = thisPin; test > 0; test--) {//check that the hearts are not the same
      if (thisCuore[thisPin] == thisCuore[test]){
        thisCuore[thisPin] = random(1,16);
      }
    }
    for (int test = thisPin; test > 0; test--) {//check that the hearts are not the same again
      if (thisCuore[thisPin] == thisCuore[test]){
        thisCuore[thisPin] = random(1,16);
      }
    }
    for (int test = thisPin; test > 0; test--) {//check that the hearts are not the same again
      if (thisCuore[thisPin] == thisCuore[test]){
        thisCuore[thisPin] = random(1,16);
      }
    }
  }
  for (y = 0; y < 9; y++)  { //reset the Average matrix
    for ( z = 0; z < 9; z++)  { 
      voce[0][y] = voce[0][y] + average[y][z];
      average[y][z]=0;
    }
  } 
}

void signatureVoce(){
  if (abs(millis()-silenceStart)>silenceDuration) {
    Serial.print("Firma Vocale --> ");
    for (int i = 1; i < 8; i++)  { 
      Serial.print (voce[0][i]);
      Serial.print ("\t");
    }
    for (int k = 1; k < 8; k++)  { 
      if (abs(voce[0][1] - voce[k][1])>signatureMin && abs(voce[0][2] - voce[k][2])>signatureMin && abs(voce[0][3] - voce[k][3])>signatureMin && abs(voce[0][4] - voce[k][4])>signatureMin && abs(voce[0][5] - voce[k][5])>signatureMin && abs(voce[0][6] - voce[k][6])>signatureMin && abs(voce[0][7] - voce[k][7])>signatureMin){
        thisVoce == k;
        for (int l = 1; l < 8; l++)  { //transfers the vocal signature to the match site.
          voce[k][l] = voce[0][l];
        }
        x = 9;
        Serial.print("Match! ::");
        Serial.print(k);
        break;
      }
      else { 
        if (k==7){
          nextVoce++;
          if (nextVoce > 8){
            reset();
          }
          Serial.print("No Match :: Assigned to ");
          Serial.println(nextVoce);
          thisVoce == nextVoce;
          for (int l = 1; l < 8; l++)  { //transfers the vocal signature to the match site.
            voce[nextVoce][l] = voce[0][l];
          }
        } 
      }
    }
    for (int i = 1; i < 8; i++)  {
      for (int j = 1; j < 8; j++) { 
        voce[0][i] = 0;
        average [j][i] = 0;
      }
    }
  }
}
































