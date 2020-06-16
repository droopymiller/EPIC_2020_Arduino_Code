//RED LED Connect to pin 9 to long lead of LED. connect short end of LED to 200 to 300 ohm resistor to GND;
//YELLO 10 Connect to pin 10 to long lead of LED. connect short end of LED to 200 to 300 ohm resistor to GND;
//GREEN 11 Connect to pin 11 to long lead of LED. connect short end of LED to 200 to 300 ohm resistor to GND;
//BLUE 12 Connect to pin 12 to long lead of LED. connect short end of LED to 200 to 300 ohm resistor to GND;
//BUZZER PIN 3 to + lead of passive buzzer.  The other lead goes to GND 

#include "pitches.h"

//notes in the melody
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};

//note durations: 4 = quarter note, 8 = eight note, etc.
int noteDurations[] = {
  8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 4, 4, 8, 8, 4, 4, 4, 2, 
};

void setup() {
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (12, OUTPUT);
// configures the pins that drive LEDs as outputs  

    
}

void loop() {
    for (int thisNote = 0 ; thisNote < 25 ; thisNote++) { 
    int randomLight1 = random(9, 13);
    int randomLight2 = random(9, 13);
    int randomLight3 = random(9, 13);
    int randomLight4 = random(9, 13);
    
    digitalWrite (randomLight1, HIGH);
    digitalWrite (randomLight2, HIGH);
    digitalWrite (randomLight3, LOW);
    digitalWrite (randomLight4, LOW);
    //digitalWrite (random(9, 12), LOW);
    
    int noteDuration = 1130/noteDurations[thisNote];
    tone (3, melody[thisNote], noteDuration);
    
    int pause = noteDuration * 1.275;
    delay (pause);
    
    noTone(3);

    
  }
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
// Turns on all LEDs so that you can blow the candles out
  delay(3000);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    
 delay(3000); 

}
