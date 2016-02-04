// original file came from the following URI.
//
//  https://github.com/sosandroid/AMS_AS5048B
//

/**************************************************************************/
/*!
    @file     angle_moving_avg.ino
    @author   SOSAndroid (E. Ha.)
    @license  BSD (see license.txt)

	read over I2C bus and averaging angle 
	
    @section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/


#include <ams_as5048b.h>
#include <Wire.h>

//unit consts
#define U_RAW 1
#define U_TRN 2
#define U_DEG 3
#define U_RAD 4
#define U_GRAD 5
#define U_MOA 6
#define U_SOA 7
#define U_MILNATO 8
#define U_MILSE 9
#define U_MILRU 10

const float p1975Diameter  = 8.5;// (mm) 8-9 mm least-most
const float filamentDiameter = 2.85;// (mm) 

float lastAngle;
float currentAngle; 
int totalRotation = 0;

float forwardDistance;
float backwardDistance;
float overallDistance;
float individualDistance; //delta change

float  degAvgExpNow, degAvgExpLast;
float  radAvgExpNow, radAvgExpLast;

float THREE_HALF_PI = HALF_PI*3;

unsigned long lastSPrintTimeMillis;
//
//Troy suggested me to have 3 different levels with different variables.
//  1. Rotation count for long scale printing.
//  2. Retraction (pulling) and Priming (pushing) measure.
//  3. Small Scale Accuracy in frequent polling (20Hz).

// And Try asked me to compare actuallity. 100mm by PronterFace and measure nd compare.


AMS_AS5048B mysensor;

void setup() {

	//Start serial
  Serial.begin(250000);
	while (!Serial) ; //wait until Serial ready
	
	//Start Wire object. Unneeded here as this is done (optionnaly) by AMS_AS5048B object (see lib code - #define USE_WIREBEGIN_ENABLED)
	//Wire.begin();

	//init AMS_AS5048B object
	mysensor.begin();
	
    //set clock wise counting
    mysensor.setClockWise(true); 
    
    //set the 0 to the sensorr
    //mysensor.zeroRegW(0x0); // dosen't work??

    delay(100);

    lastSPrintTimeMillis= 0;
    degAvgExpLast = mysensor.angleR(U_DEG, true);
    radAvgExpLast = mysensor.angleR(U_RAD, false);
    
}

void loop() {
	unsigned long timeMillis= millis();
    //prints to serial the read angle in degree and its average every 2 seconds
	//prints 2 times the exact same angle - only one measurement
  
    mysensor.updateMovingAvgExp();

  degAvgExpNow= mysensor.getMovingAvgExp(U_DEG);
  radAvgExpNow= mysensor.getMovingAvgExp(U_RAD);
  
  //detecting the rotation count (in radian).
  if(radAvgExpNow-radAvgExpLast >PI) {
    if(radAvgExpNow>THREE_HALF_PI && radAvgExpLast <HALF_PI ) totalRotation --;  // clockwise is Backward on primal (right) feeder
  }
  else if(radAvgExpLast-radAvgExpNow > PI) {
    if(radAvgExpNow<HALF_PI && radAvgExpLast >THREE_HALF_PI ) totalRotation ++;  // Conter-Clockwise is Forward on primal (right) feeder
  }
  radAvgExpLast= radAvgExpNow;
  
  if(timeMillis - lastSPrintTimeMillis  > 14) { // data output ratio
     lastSPrintTimeMillis = timeMillis;
  
      Serial.print(timeMillis);
      Serial.print(" ");//    Serial.println(" ms");
      
      Serial.print(totalRotation); 
      Serial.print(" ");//    rotations
      
      Serial.print(degAvgExpNow);
      Serial.print(" ");//    Serial.print(" deg");
      
      Serial.print(radAvgExpNow * 1000.0); // MULTIPLIED 1000 x to get more resolution
      Serial.print(" ");//    Serial.print(" rad");
   
      Serial.println(mysensor.angleR(U_DEG, false));  // last pure data (not average)
      //Serial.println(" ");//    Serial.print(" deg");
   
  }

	delay(3); // average data update ratio 
}

