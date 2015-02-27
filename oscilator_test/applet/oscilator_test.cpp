/*
Oscilator test sequence
 http://www.troykyo.com
 */
#include "WProgram.h"
void setup();
void loop ();
unsigned long time ;                 // time control 1
unsigned long inTime ;               // last time sequence was initiated
unsigned long beat ;                 // Single time trial

void setup() {
Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
}


void loop () {
    Serial.print("Time ");
    time == millis();
    Serial.println(time);
    /*Serial.print("     ");
    Serial.print("inTime ");
    Serial.print(inTime);
    beat == ((time - inTime));
    Serial.print(beat);
    Serial.print("     ");
    inTime == time;*/
    Serial.println();
    delay(1000);  
}


int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

