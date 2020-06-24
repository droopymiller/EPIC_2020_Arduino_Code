//www.elegoo.com
//2016.12.08
// Written by Dr. Derickson
// Modified by Drew Miller
// Instructions - Connect a 200 to 500 ohm resistor from pin 2 to 5V
// Instructions - connect button from pin 2 to GND
// Instructions - connect Servo to 5V, GND, and pin 9
// Instructions - make sure and load the servo library function prior to running this program
// Operation This program will wait until the button is pressed and then move the Servo to let a ball go in the Rube Goldberg project
// The ultrasonic sensor is now hooked up to measure distance in addition to the servo and switch
// plays music at the end with the passive speaker

#include <Servo.h>
#include "SR04.h"
#include "pitches.h"

Servo myservo;
#define TRIG_PIN    12
#define ECHO_PIN    11
#define ENABLE      5
#define DIRA        3
#define DIRB        4
#define BUZZER      8
#define BUTTON      2
#define LED_PIN     13

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;             // 500 miliseconds
int pos = 0;                    // variable to store the servo position

void setup()
{
    pinMode(LED_PIN, OUTPUT);  // initialize the ledPin as an output
    pinMode(BUTTON, INPUT);    // initialize pin 2 as an input for the ball switch
    pinMode(ENABLE, OUTPUT);
    pinMode(DIRA, OUTPUT);
    pinMode(DIRB, OUTPUT);
    myservo.attach(9);         // connect pin 9 with the control line (Orange Wire)
    Serial.begin(9600);
    delay(1000);
    digitalWrite(ENABLE,LOW); // enable off
    //digitalWrite(DIRA,HIGH); // full speed direction a

}

void loop()
{
    int digitalVal = digitalRead(2);        // Read pin 2 which is connected to the button
    if(LOW == digitalVal) {
        digitalWrite(LED_PIN,HIGH);         // Turn the led on
        for (pos = 0; pos <= 180; pos += 1) {   // goes from 0 degrees to 180 degrees
                                                // in steps of 1 degree
            myservo.write(pos);                 // tell servo to go to position in variable 'pos'
            delay(15);                          // waits 15ms for the servo to reach the position
        }
        for (pos = 180; pos >= 0; pos -= 1) {   // goes from 180 degrees to 0 degrees
            myservo.write(pos);                 // tell servo to go to position in variable 'pos'
            delay(15);                          // waits 15ms for the servo to reach the position
        }
        digitalWrite(LED_PIN,LOW);  //turn the led off
        delay(5000);                // Adjust this delay to allow marble to land in boat
        digitalWrite(DIRA,HIGH);    // full speed direction a
        analogWrite(ENABLE,128);    // enable on, Adjustable speed 0-255
    }
    a = sr04.Distance();        // Set a to distance in cm
    Serial.print(a);            // Print distance a to serial monitor
    Serial.println("cm");       // Print units to serial monitor
    delay(200);
    if(a < 5.0) {               // If distance a is less than 5 cm
        for (int thisNote = 0; thisNote < 8; thisNote++) {
            // pin8 output the voice, every scale is 0.5 sencond
            tone(8, melody[thisNote], duration);
            delay(1000);
            digitalWrite(ENABLE,LOW); // enable off
        }
    }
}
