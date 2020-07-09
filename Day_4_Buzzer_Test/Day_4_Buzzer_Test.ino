//www.elegoo.com
//2016.12.08
// This is a simple program to make sure the passive buzzer works
// The passive buzzer positive terminal should go to the arduino uno pin 8
// The passive buzzer negative termal should go to GND on the arduino
// The passive buzzer will play two notes just to verify that everything is working.

// notes in the melody:
int melody[] = {300, 400};
int duration = 500;  // 500 miliseconds

void setup() {

}

void loop() {
    tone(8, melody[1], duration);
    delay(500);
    tone(8, melody[2], duration);
    delay(500);

}
