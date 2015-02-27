 
#include <math.h>

#include "Wire.h"
#include "WiiChuck.h"
#include "nunchuck_funcs.h"

#define MAXANGLE 90
#define MINANGLE -9ds0


WiiChuck chuck = WiiChuck();
int angleStart, currentAngle;
int tillerStart = 0;
double angle;

void setup() {
  //nunchuck_init();
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
  //chuck.calibrateJoy();
}


void loop() {
  delay(20);
  chuck.update(); 

     Serial.print("Roll ");
  Serial.print(chuck.readRoll());
    Serial.print(", Pitch ");  
  Serial.print(chuck.readPitch());
    Serial.print(", X ");  

    Serial.print((int)chuck.readAccelX()); 
    Serial.print(", Y ");  
    Serial.print((int)chuck.readAccelY()); 
    Serial.print(", Z ");  

    Serial.print((int)chuck.readAccelZ()); 

    Serial.println();

}
