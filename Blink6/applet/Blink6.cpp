/*
 * Blink
 *
 * The basic Arduino example.  Turns on an LED on for one second,
 * then off for one second, and so on...  We use pin 13 because,
 * depending on your Arduino board, it has either a built-in LED
 * or a built-in resistor so that you need only an LED.
 *
 * http://www.arduino.cc/en/Tutorial/Blink
 */

#include "WProgram.h"
void setup();
void loop();
int ledPin13 = 13;                // LED connected to digital pin 13
int ledPin12 = 12;              // LED connected to digital pin 12
int ledPin11 = 11;                // LED connected to digital pin 13
int ledPin10 = 10;              // LED connected to digital pin 12
int ledPin9 = 9;                // LED connected to digital pin 13
int ledPin8 = 8;              // LED connected to digital pin 12
int ledint = 100;                      // timing number
int i;                            // loop monitor

void setup()                    // run once, when the sketch starts
{
  pinMode(ledPin13, OUTPUT);      // sets the digital pin as output
  pinMode(ledPin12, OUTPUT);     // sets the digital pin as output
  pinMode(ledPin11, OUTPUT);      // sets the digital pin as output
  pinMode(ledPin10, OUTPUT);     // sets the digital pin as output
  pinMode(ledPin9, OUTPUT);      // sets the digital pin as output
  pinMode(ledPin8, OUTPUT);     // sets the digital pin as output
}

void loop()                     // run over and over again
{
i = 0;
for (i = 0; i < 6; i++)
 {
     digitalWrite(ledPin13, LOW);   // sets the LED off istruzioni che leggono \u201cx\u201d
     digitalWrite(ledPin12, LOW);   // sets the LED off
     digitalWrite(ledPin11, LOW);   // sets the LED off
     digitalWrite(ledPin13, LOW);   // sets the LED off istruzioni che leggono \u201cx\u201d
     digitalWrite(ledPin12, LOW);   // sets the LED off
     digitalWrite(ledPin11, LOW);   // sets the LED off     
     delay(ledint);
    
    if (i = 1)
    {
        digitalWrite(ledPin13, HIGH);   // sets the LED on
        delay(ledint);                  // waits for a second
        // salta all\u2019i successivo
        continue;
    }    
    
    if (i = 2)
    {
        digitalWrite(ledPin12, HIGH);   // sets the LED on
        delay(ledint);                  // waits for a second
        // salta all\u2019i successivo
        continue;
    }
    
    if (i = 3)
    {
        digitalWrite(ledPin11, HIGH);   // sets the LED on
        delay(ledint);                  // waits for a second
        // salta all\u2019i successivo
        continue;
    }
    
    if (i = 4)
    {
        digitalWrite(ledPin10, HIGH);   // sets the LED on
        delay(ledint);                  // waits for a second
        // salta all\u2019i successivo
        continue;
    }
    
    if (i = 5)
    {
        digitalWrite(ledPin9, HIGH);   // sets the LED on
        delay(ledint);                  // waits for a second
        // salta all\u2019i successivo
        continue;
    }
    
    if (i = 6)
    {
        digitalWrite(ledPin8, HIGH);   // sets the LED on
        delay(ledint);                  // waits for a second
        // salta all\u2019i successivo
        continue;
    }
    
    if (i > 100)
    {
        // salta all\u2019i successivo
        continue;
    }

    if (i < 0)
    {
        break;
    }
 }
}  

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

