/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_F3, NOTE_DS3, NOTE_F3, NOTE_DS3, NOTE_C3, NOTE_GS2, NOTE_D3, 0,
  NOTE_F3, NOTE_G3, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_D3, NOTE_E3, NOTE_D3, 0, 
  NOTE_D3, NOTE_E3, NOTE_D3, NOTE_E3, NOTE_AS3,
  NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_G3,
  NOTE_A4, NOTE_F3, NOTE_AS4, NOTE_A4, NOTE_F3, NOTE_AS4,
  NOTE_GS3, NOTE_F3, NOTE_AS4, NOTE_GS3, NOTE_F3, 0,
  NOTE_DS3, NOTE_C3, NOTE_F3
};

// note durations:
int noteDurations[] = {
  1000, 250, 250, 500, 750, 250, 1000, 1500,
  1000, 250, 250, 500, 500, 250, 250, 1500, 1500,
  750, 500, 250, 750, 750,
  750, 500, 250, 750, 750,
  750, 500, 250, 750, 500, 250,
  750, 500, 250, 750, 750, 750,
  250, 250, 3000
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 42; thisNote++) {
    if(melody[thisNote] == 0){
      noTone(11);
    } else {
      tone(11, melody[thisNote]);
    }
    delay(noteDurations[thisNote]);

    // stop the tone playing:
    noTone(11);
    // to distinguish the notes, set a minimum time between them.
    delay(100);
  }
}

void loop() {
  // no need to repeat the melody.
}
