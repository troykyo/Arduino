int cuore[] = { 
  -1,  2, 3, 4, 5, 6,  7,42,44, 8, 9, 45,10,11,12,13, 46 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)

int mic[] = { 
  -1, A8, A9, A10, A11, A12, A13, A14};       // an array of analog input pins numbers to which the colororganic spectralized is attached
int freq[7];

int qualeCuore[16];

void setup() {
  Serial.begin(9600);
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:

  for (int thisPin = 1; thisPin < 16; thisPin++)  {
    pinMode(cuore[thisPin], OUTPUT);
    digitalWrite (thisPin, HIGH);   
  }
  for (int thisPin = 1; thisPin < 8; thisPin++)  {
    pinMode(mic[thisPin], INPUT);      
  }
  delay (500);//blink the cuori for half a second (boot test)
  for (int thisPin = 1; thisPin < 16; thisPin++)  {
    digitalWrite (thisPin, LOW);   
  }
}

void loop() {


  Serial.println();

  for (int thisPin = 1; thisPin < 17; thisPin++)  {

    digitalWrite (cuore[thisPin],HIGH);
    delay (500);   
        digitalWrite (cuore[thisPin-1],LOW);

   
  }
}






