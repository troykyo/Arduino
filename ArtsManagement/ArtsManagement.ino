/*
Read the distance from a distance sensor and if the distance read is less than 80 cm plays an mp3 player.
 */


// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.

const int numReadings = 10;
const int play = 10;
const int inputPin = A0;
const int activationDistance =70;
const int audio = 8 ; //in seconds

int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int calabrateMin = 0; 
int calabrateMax = 0; 
long time = 0;
long startTime = 0;
long playTime = 0;



void setup()
{
  // initialize serial communication with computer:
  Serial.begin(9600);                   
  // initialize all the readings to 0: 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;          
  pinMode (play,OUTPUT);
  pinMode (inputPin, INPUT);
}

void loop() {
  time = millis();
  // subtract the last reading:
  total = total - readings[index];         
  // read from the sensor:  
  readings[index] = analogRead(inputPin); 
  // add the reading to the total:
  total= total + readings[index];       
  // advance to the next position in the array:  
  index = index + 1;                    

  // if we're at the end of the array...
  if (index >= numReadings)              
    // ...wrap around to the beginning: 
    index = 0;                           

  // calculate the average:
  average = total / numReadings;         
  // send it to the computer as ASCII digits
  Serial.print(time-startTime); 
  Serial.print("  "); 

  Serial.println(average);   
  if ((average > activationDistance) && (abs(time-startTime) > (audio*1000))){
    startTime = millis();
    digitalWrite (play, HIGH); //press play
    digitalWrite (13, LOW); //press play
    delay (400);
    digitalWrite (play, LOW); // stop Pressing play
    digitalWrite (13, HIGH); //press play
      delay (10n000);
     digitalWrite (play, HIGH); //press play
     digitalWrite (13, LOW); //press play
     delay (300);
     digitalWrite (play, LOW); // stop Pressing play
     digitalWrite (13, HIGH); //press play
    
  }
  delay(1);        // delay in between reads for stability            
}





