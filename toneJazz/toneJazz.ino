/*
  Melody
 
 Plays a melody 
 
 circuit:
 * 8-ohm speaker on digital pin 8
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe 
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_A1, NOTE_A2,NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6, NOTE_A7,0};
int keyofC [] = {
  NOTE_B0,
  NOTE_C1  ,
  //NOTE_CS1 ,
  NOTE_D1  ,
  //NOTE_DS1 ,
  NOTE_E1  ,
  NOTE_F1  ,
  // NOTE_FS1 ,
  NOTE_G1  ,
   //NOTE_GS1 ,
  NOTE_A1  ,
   //NOTE_AS1 ,
  NOTE_B1  ,
  NOTE_C2  ,
   //NOTE_CS2 ,
  NOTE_D2  ,
  // NOTE_DS2 ,
  NOTE_E2  ,
  NOTE_F2  ,
  // NOTE_FS2 ,
  NOTE_G2  ,
  // NOTE_GS2 ,
  NOTE_A2  ,
   //NOTE_AS2 ,
  NOTE_B2  ,
  NOTE_C3  ,
   //NOTE_CS3 ,
  NOTE_D3  ,
   //NOTE_DS3 ,
  NOTE_E3  ,
  NOTE_F3  ,
  // NOTE_FS3 ,
  NOTE_G3  ,
   //NOTE_GS3 ,
  NOTE_A3  ,
   //NOTE_AS3 ,
  NOTE_B3  ,
  NOTE_C4  ,
  // NOTE_CS4 ,
  NOTE_D4  ,
  // NOTE_DS4 ,
  NOTE_E4  ,
  NOTE_F4  ,
  // NOTE_FS4 ,
  NOTE_G4  ,
   //NOTE_GS4 ,
  NOTE_A4  ,
   //NOTE_AS4 ,
  NOTE_B4  ,
  NOTE_C5  ,
   //NOTE_CS5 ,
  NOTE_D5  ,
   //NOTE_DS5 ,
  NOTE_E5  ,
  NOTE_F5  ,
   //NOTE_FS5 ,
  NOTE_G5  ,
   //NOTE_GS5 ,
  NOTE_A5  ,
  // NOTE_AS5 ,
  NOTE_B5  ,
  NOTE_C6  ,
   //NOTE_CS6 ,
  NOTE_D6  ,
   //NOTE_DS6 ,
  NOTE_E6  ,
  NOTE_F6  ,
   //NOTE_FS6 ,
  NOTE_G6  ,
   //NOTE_GS6 ,
  NOTE_A6  ,
   //NOTE_AS6 ,
  NOTE_B6  ,
  NOTE_C7  ,
   //NOTE_CS7 ,
  NOTE_D7  ,
   //NOTE_DS7 ,
  NOTE_E7  ,
  NOTE_F7  ,
   //NOTE_FS7 ,
  NOTE_G7  ,
   //NOTE_GS7 ,
  NOTE_A7  ,
   //NOTE_AS7 ,
  NOTE_B7  ,
  NOTE_C8  ,
   //NOTE_CS8 ,
  NOTE_D8  
   //,NOTE_DS8 
 };

int noteDuration = 0;
unsigned int pitch = 0;
unsigned int pitchMatch = 0;
unsigned int lastPitch = 0;
unsigned int time =0;
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8, 8, 8, 8,8,8,8,8 };

void setup() {
  // iterate over the notes of the melody:
  Serial.begin(9600);
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = random(1,8);
    unsigned int pitch = random(1,4000);

    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    noteDuration = 1000/random(1,16);
    while (noteDuration%4 != 0){
      noteDuration = 1000/random(1,16);
    }

    pitch = random(1,2000);

    if (pitch > 1000){
      pitch = random(1,2000);
    }
    while (pitchMatch == 0){
      pitch++;
      for (int thisNote = 0; thisNote < 51; thisNote++) {
        if (pitch == keyofC[thisNote]){
          pitchMatch = 1;
        }
        if (pitch > 2000){
          pitch = random(1,2000);
          break;
        }
      }
    }
    Serial.print(lastPitch);
    Serial.print("\t");
    Serial.print(pitch);
    Serial.print("\t");
   Serial.println(noteDuration);
    if (random(0,10)>9){
      while (lastPitch > pitch){
        lastPitch--;
        tone(8, lastPitch,1000);
        Serial.print("-");
      }
      while (lastPitch  < pitch){
        lastPitch++;
        tone(8, lastPitch, 1000);
        Serial.print("+");
      }
    }
    Serial.println("*");
    tone(8, pitch,noteDuration);

    lastPitch = pitch;
    pitchMatch == 0;
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}





