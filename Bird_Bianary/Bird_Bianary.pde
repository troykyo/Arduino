/*
Controls 16 mecahanical birds

This is the Local client that reads 
 */
 //constants
const int whichMaster = 1;
const int chirplength = 5000;

//Variables 
unsigned long n;
int bird[] = {12,11,9,8,7,6,5,4,3,2,14,15,16,17,18,19}; //array for bird pins
int birdA[] = {-1,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0}; //array for bird pins
int whichbird = 0; // Counter for selecting bird.
int whichbird2 = 0; // Counter for selecting bird.
int birdonoff;
 

void setup() {
  Serial.begin(9600);
delay (2000);
}

void turnonthebird() {
  for (n=0; n<8; n++){
    birdonoff = bitRead((birdA[(whichMaster)]),n);
    if (birdonoff == 0){
       digitalWrite((bird[(n)])),LOW;
       Serial.print ("off ");}
    if (birdonoff == 1){
       digitalWrite((bird[(n)])),HIGH;
       Serial.print ("on  ");}  
    birdonoff = bitRead((birdA[(whichMaster)]),n);
    if (birdonoff == 0){
       digitalWrite((bird[((n+16))])),LOW;
       Serial.print ("OFF ");}
    if (birdonoff == 1){
       digitalWrite((bird[((n+16))])),HIGH;
       Serial.print ("ON  ");}   
  }
}

void loop() {
Serial.print("Chirp ");
birdA[(whichMaster)] = random (0,255);
Serial.print (birdA[(whichMaster)]);
Serial.print (" ");
birdA[(whichMaster+16)] = random (0,255);
Serial.print (birdA[(whichMaster+16)]);
Serial.print (" ");
turnonthebird();
delay(chirplength);
}
}



