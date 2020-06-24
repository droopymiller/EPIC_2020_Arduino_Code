/*******************************************************************************
 * Libraries
 ******************************************************************************/
 #define NOTE_B0  31
 #define NOTE_C1  33
 #define NOTE_CS1 35
 #define NOTE_D1  37
 #define NOTE_DS1 39
 #define NOTE_E1  41
 #define NOTE_F1  44
 #define NOTE_FS1 46
 #define NOTE_G1  49
 #define NOTE_GS1 52
 #define NOTE_A1  55
 #define NOTE_AS1 58
 #define NOTE_B1  62
 #define NOTE_C2  65
 #define NOTE_CS2 69
 #define NOTE_D2  73
 #define NOTE_DS2 78
 #define NOTE_E2  82
 #define NOTE_F2  87
 #define NOTE_FS2 93
 #define NOTE_G2  98
 #define NOTE_GS2 104
 #define NOTE_A2  110
 #define NOTE_AS2 117
 #define NOTE_B2  123
 #define NOTE_C3  131
 #define NOTE_CS3 139
 #define NOTE_D3  147
 #define NOTE_DS3 156
 #define NOTE_E3  165
 #define NOTE_F3  175
 #define NOTE_FS3 185
 #define NOTE_G3  196
 #define NOTE_GS3 208
 #define NOTE_A3  220
 #define NOTE_AS3 233
 #define NOTE_B3  247
 #define NOTE_C4  262
 #define NOTE_CS4 277
 #define NOTE_D4  294
 #define NOTE_DS4 311
 #define NOTE_E4  330
 #define NOTE_F4  349
 #define NOTE_FS4 370
 #define NOTE_G4  392
 #define NOTE_GS4 415
 #define NOTE_A4  440
 #define NOTE_AS4 466
 #define NOTE_B4  494
 #define NOTE_C5  523
 #define NOTE_CS5 554
 #define NOTE_D5  587
 #define NOTE_DS5 622
 #define NOTE_E5  659
 #define NOTE_F5  698
 #define NOTE_FS5 740
 #define NOTE_G5  784
 #define NOTE_GS5 831
 #define NOTE_A5  880
 #define NOTE_AS5 932
 #define NOTE_B5  988
 #define NOTE_C6  1047
 #define NOTE_CS6 1109
 #define NOTE_D6  1175
 #define NOTE_DS6 1245
 #define NOTE_E6  1319
 #define NOTE_F6  1397
 #define NOTE_FS6 1480
 #define NOTE_G6  1568
 #define NOTE_GS6 1661
 #define NOTE_A6  1760
 #define NOTE_AS6 1865
 #define NOTE_B6  1976
 #define NOTE_C7  2093
 #define NOTE_CS7 2217
 #define NOTE_D7  2349
 #define NOTE_DS7 2489
 #define NOTE_E7  2637
 #define NOTE_F7  2794
 #define NOTE_FS7 2960
 #define NOTE_G7  3136
 #define NOTE_GS7 3322
 #define NOTE_A7  3520
 #define NOTE_AS7 3729
 #define NOTE_B7  3951
 #define NOTE_C8  4186
 #define NOTE_CS8 4435
 #define NOTE_D8  4699
 #define NOTE_DS8 4978


/*******************************************************************************
 * Main Code
 ******************************************************************************/

//LED1: Connect to pin 9 to long lead of LED. Connect short end of LED to 200 to 500 ohm resistor to GND;
//LED2: Connect to pin 10 to long lead of LED. Connect short end of LED to 200 to 500 ohm resistor to GND;
//LED3: Connect to pin 11 to long lead of LED. Connect short end of LED to 200 to 500 ohm resistor to GND;
//LED4: Connect to pin 12 to long lead of LED. Connect short end of LED to 200 to 500 ohm resistor to GND;
//BUZZER PIN 3 to positive (+) lead of passive buzzer.  The other lead goes to GND

// Original code supplied by Dr. Derickson
// Edited and documented by Gerome Cacho

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
