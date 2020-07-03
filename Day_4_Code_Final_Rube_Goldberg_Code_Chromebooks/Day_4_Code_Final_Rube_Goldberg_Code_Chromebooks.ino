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

 #ifndef SR04_H
 #define SR04_H

 #if defined(ARDUINO) && ARDUINO >= 100
 	#include "Arduino.h"
 #else
 	#include "WProgram.h"
 #endif
 //#include "pins_arduino.h"

 #include <inttypes.h>

 #define PULSE_TIMEOUT 150000L	// 100ms
 #define DEFAULT_DELAY 10
 #define DEFAULT_PINGS 5
 class SR04 {
 public:

 	/**
 	* Constructor
 	* Ultrasonic sensor SR04, four connections pins
 	* VCC, ECHO, TRIGGER, GND
 	* <br>
 	* \param echoPin digital INPUT-Pin for measuring distance
 	* \param triggerPin if 10us high a trigger signal is generated from
 	*					SR04
 	*
 	* \return void
 	*/
 	SR04(int echoPin, int triggerPin);

 	/**
 	* Do a measurment for this sensor. Return distance as long
 	* in centimenter
 	* \return long distance in centimeter
 	*/
 	long Distance();

 	/**
 	* Do count measurents and calculate the average.
 	* To avoid defilement from ow/high peaks, min/max values
 	* are substracted from the average
 	*
 	* \param wait delay between measurements, default = DEFAULT_DELAY/ms
 	* \param count number of measurements, default DEFAULT_PINGS
 	* \return long distance in centimeter
 	**/
 	long DistanceAvg(int wait=DEFAULT_DELAY, int count=DEFAULT_PINGS);

 	/**
 	* Do only a ping. Get result with methode getDistance()
 	*
 	* \param keine
 	*/
 	void Ping() ;

 	/**
 	* return latest distance. Methode Ping() should be called before
 	* \param keine
 	* \return Distanz in Zentimeter
 	*/
 	long getDistance();


 private:
 	/**
 	* Do the measurement calculation and return result in centimeter
 	* SR04 measure echo time to obstacle and return way.
 	* <br>
 	* Sound travels with 340m/sec
 	* <br>
 	* Example: Obstace 100cm away from SR04. Measure time is 100cm to
 	* obstacle and 100cm return = 200cm
 	* <br>
 	* 1sec = 1000ms = 1.000.000uS
 	* 1.000.000 / 340 = Distance in microseconds for 100cm
 	* 2941uS fuer 100cm = 5882 uS fuer 200cm
 	*
 	* duration / 5882 * 100 = distance in cm
 	*/
 	long MicrosecondsToCentimeter(long duration);

 	long _currentDistance;
 	int _echoPin, _triggerPin;
 	long _duration, _distance;
 	bool _autoMode;
 };
 #endif

 SR04::SR04(int echoPin, int triggerPin) {
     _echoPin = echoPin;
     _triggerPin = triggerPin;
     pinMode(_echoPin, INPUT);
     pinMode(_triggerPin, OUTPUT);
     _autoMode = false;
     _distance = 999;
 }


 long SR04::Distance() {
     long d = 0;
     _duration = 0;
     digitalWrite(_triggerPin, LOW);
     delayMicroseconds(2);
     digitalWrite(_triggerPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(_triggerPin, LOW);
     delayMicroseconds(2);
     _duration = pulseIn(_echoPin, HIGH, PULSE_TIMEOUT);
     d = MicrosecondsToCentimeter(_duration);
     delay(25);
     return d;
 }

 long SR04::DistanceAvg(int wait, int count) {
     long min, max, avg, d;
     min = 999;
     max = 0;
     avg = d = 0;

     if (wait < 25) {
         wait = 25;
     }

     if (count < 1) {
         count = 1;
     }

     for (int x = 0; x < count + 2; x++) {
         d = Distance();

         if (d < min) {
             min = d;
         }

         if (d > max) {
             max = d;
         }

         avg += d;
     }

     // substract highest and lowest value
     avg -= (max + min);
     // calculate average
     avg /= count;
     return avg;
 }

 void SR04::Ping() {
     _distance = Distance();
 }

 long SR04::getDistance() {
     return _distance;
 }

 long SR04::MicrosecondsToCentimeter(long duration) {
     long d = (duration * 100) / 5882;
     //d = (d == 0)?999:d;
     return d;
 }

/*******************************************************************************
 * Main Code
 ******************************************************************************/

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
        digitalWrite(DIRB,LOW);    // full speed direction a
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
