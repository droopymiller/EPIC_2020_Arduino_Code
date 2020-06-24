//LED1: Connect to pin 9 to long lead of LED. Connect short end of LED to 200 to 500 ohm resistor to GND;
//LED2: Connect to pin 10 to long lead of LED. Connect short end of LED to 200 to 500 ohm resistor to GND;
//LED3: Connect to pin 11 to long lead of LED. Connect short end of LED to 200 to 500 ohm resistor to GND;
//LED4: Connect to pin 12 to long lead of LED. Connect short end of LED to 200 to 500 ohm resistor to GND;
//BUZZER PIN 3 to positive (+) lead of passive buzzer.  The other lead goes to GND

// Original code supplied by Dr. Derickson
// Edited and documented by Gerome Cacho

#include "pitches.h"    // Library

//25 notes in the melody
int melody[] = {NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_D4,
                NOTE_C4, NOTE_G4, NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4,
                NOTE_D4, NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4};

//note durations: 4 = quarter note, 8 = eight note, etc.
int noteDurations[] = {8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 4, 4, 8, 8, 4, 4, 4, 2};

float tempo = 1.275;    // default is 1.275. Could try .7, .9

void setup() {
  // Runs once
  pinMode(9, OUTPUT);   // configures the pins that drive LEDs as outputs
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  // Runs forever
    for (int thisNote = 0 ; thisNote < 25 ; thisNote++)     // For 25 times
    {
      int randomLight1 = random(9, 13);                     // RNG select the pins
      int randomLight2 = random(9, 13);                     // RNG meaning "Random Number Generator" which is the computer's way to determining randomness
      int randomLight3 = random(9, 13);
      int randomLight4 = random(9, 13);

      digitalWrite(randomLight1, HIGH);                     // Tell the pins to go high or low
      digitalWrite(randomLight2, HIGH);
      digitalWrite(randomLight3, LOW);
      digitalWrite(randomLight4, LOW);

      int noteDuration = 1130/noteDurations[thisNote];      // Creates duration of the note
      tone(3, melody[thisNote], noteDuration);              // Sends audio signal to pin 3 aka speaker. Plays thisNote for noteDuration.

      int pause = noteDuration * tempo;                     // Calculates a pause to play between notes
      delay(pause);

      noTone(3);                                            // Mutes the audio signal on pin 3
    }
                                                            // After looping 25 times
    digitalWrite(9, HIGH);                                  // Send everything high
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);

    delay(3000);                                            // Turns on all LEDs so that you can blow the candles out

    digitalWrite(9, LOW);                                   // Send everything low. Candles are blown
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);

    delay(3000);                                            // Wait for 3s before going through void loop again
}
