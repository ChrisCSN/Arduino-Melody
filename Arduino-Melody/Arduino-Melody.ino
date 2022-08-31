/*
  Based on Tom Igoe's code
  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"
const int buttonPin = 3;
const int buzzerPin = 2;
static int red = 5;
static int blue = 6;
static int yellow = 7;
static int green = 8;

// notes in the melody:
// use 0 for a rest
// put each measure on its own line
int buttonState = 0;
int melody[] = {
  NOTE_G3, NOTE_G3, NOTE_A4, NOTE_G3, NOTE_C4, NOTE_B4, 0,
  NOTE_G3, NOTE_G3, NOTE_A4, NOTE_G3, NOTE_D5, NOTE_C5, 
  NOTE_G3, NOTE_G3,NOTE_G3, NOTE_E4, NOTE_C4, NOTE_B4, NOTE_A4,
  NOTE_F3, NOTE_F3, NOTE_E3, NOTE_C3, NOTE_D3, NOTE_C3
  
};

// note durations: 1 = whole note, 4 = quarter note, 8 = eighth note, etc.:
// be sure each note or rest in the melody above has a corresponding duration below
// put each measure on its own line
int noteDurations[] = {
  4, 4, 4, 4, 4, 6, 8,
  4, 4, 4, 4, 4, 6, 8,
  4, 4, 4, 4, 4, 4, 4, 8,
  4, 4, 4, 4, 4, 6, 8
};

// set the tempo
// a tempo of 60 is one beat per second
// a tempo of 120 would be twice as fast
int beatsPerMinute = 60;

void setup() {
pinMode(red, OUTPUT);
pinMode(blue, OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(green, OUTPUT);
pinMode(buttonPin, INPUT);

}

void loop() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    playSong();
    digitalWrite(red, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);
    delay(500);
  }   else { 
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
   }
}

void playSong(){
  // iterate over the notes of the melody:
  int len = sizeof(melody)/sizeof(melody[0]);
  for (int thisNote = 0; thisNote < len; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = static_cast<int>(1000 / noteDurations[thisNote] * 60 / beatsPerMinute);
    tone(buzzerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
  }
  // Pause before playing again
  delay(1000);
}
