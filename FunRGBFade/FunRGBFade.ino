/*
 Fun brightness blinking
 */

int brightness[4] = { 
  -1, 128, 128, 128};       // an array of pin numbers to which LEDs are attached
int pinCount = 4;           // the number of pins (i.e. the length of the array)
int R = 6;
int G = 11;
int B = 10;
int newBrightness=0;

void setup() {
  pinMode(R, OUTPUT);      
  pinMode(G, OUTPUT);      
  pinMode(B, OUTPUT);      
  Serial.begin(9600);
  Serial.print("R");
  Serial.print("\t");
  Serial.print("G");
  Serial.print("\t");
  Serial.println("B");

}


void loop() {
  // loop from the lowest pin to the highest:
  for (int i = 1; i < pinCount; i++) { 
    // turn the pin on:
    newBrightness=(abs(random(brightness[i]-10,brightness[i]+10)));
    brightness[i]= constrain(newBrightness,0,255);
  }
  analogWrite(R, brightness[1]);   
  analogWrite(G, brightness[2]);   
  analogWrite(B, brightness[3]);  
  Serial.print(brightness[1]);
  Serial.print("\t");
  Serial.print(brightness[2]);
  Serial.print("\t");
  Serial.println(brightness[3]);
  delay(10);
}




