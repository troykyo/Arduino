/*  Flicker an LED like a candle on ports 3,5,6,9,10,11 using PWM
 by Troy Nachtigall 
 www.troykyo.com 
 */

//constants
const int led = 10;
const int voce[] = {97,97,43,107,137,26,219,69,185,59,205,308,264,361,310,628,701,556,463,701,638,989,145,1134,1411,928,1243,1007,1019,1309,1013,946,856,856,593,523,732,818,1010,501,1034,907,665,591,978,958,497,426,733,550,396,278,355,306,478,453,762,214,604,905,368,1063,603,293,1600,356,848,1306,436,1393,378,583,920,316,699,755,257,658,778,164,903,120,351,584,36,302,343,284,376,33,414,227,511,227,440,326,406,446,167,784,384,593,646,82,899,361,349,779,35,841,385,450,706,135,668,363,214,493,354,247,785,260,589,519,701,759,257,607,470,596,465,194,791,517,438,437,289,556,414,380,251,414,225,362,96,40,390,167,498,72,337,463,461,398,125,449,324,543,384,252,295,214,288,61,263,181,313,328,312,383,196,683,327,609,518,370,673,102,358,436,127,600,122,363,345,492,482,381,284,101,362,117,185,187,242,151,659,342,763,302,405,272,445,762,668,758,407,220,176,154,41,350,187,873,197,766,98,352,380,472,456,634,527,342,738,255,640,423,275,662,642,816,670,444,497,528,640,742,986,811,857,534,566,298,630,743,901,823,1113,692,775,723,276,524,76
};
int flickerIntensity; // how bright each individual Flicker is
int maxFlickerIntensity = 225 ; // Maximum brightness for each individual Flicker
int minFlickerIntensity =200; // Miniimum brightness for each individual Flicker
unsigned long flickerLongevity; //duration array for each individual Flicker of the LEDs 
int maxFlickerLongevity = 100; // Maximum time in millaseconds for each individual Flicker
int minFlickerLongevity = 50; // Minimum time in millaseconds for each individual Flicker
unsigned long currentTime = 0; // Variable for the program to ask for the current time.

void setup() {
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
 
  pinMode(led, OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but effications
 
  Serial.begin(9600); // Serial for Testing
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(led, fadeValue);   
    }    
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 


void loop() {

  for (int i = 1;i<270;i++){ // loop to set each LED
      flickerLongevity = (random (minFlickerLongevity,maxFlickerLongevity)); // select a new random longevity and add it to the current time
      flickerIntensity=voce[i];
      flickerIntensity=map(flickerIntensity,26,1600,127,255);
      analogWrite(led, flickerIntensity);   // write the Flicker to the LED
      delay (flickerLongevity);
Serial.print(voce[i]); // which LED
Serial.print (" "); // Space
Serial.println(flickerIntensity); //at what time
    }
  }

