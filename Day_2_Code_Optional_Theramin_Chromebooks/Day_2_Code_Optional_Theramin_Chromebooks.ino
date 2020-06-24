/*******************************************************************************
 * Libraries
 ******************************************************************************/
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

#define TRIG_PIN 12 //here we use pins 11+12, you can use whichever digital PWM you want
#define ECHO_PIN 11

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN); //initialize our ultrasonic sensor
long dist; //our distance variable
int buzzer = 8; //buzzer pin

void setup() {
  Serial.begin(9600); //debugging purposes
  pinMode(buzzer, OUTPUT);
}

void loop() {
   dist = sr04.Distance(); //get distance
   Serial.println(dist); //print to serial for debugging
   //delay(100); you'll need this if you use the serial monitor so you don't get overwhelmed
   if (not (dist > 1000)) { //so we don't get annoying high-pitch squeacks if we get a bad reading
    tone(buzzer, dist*10 + 200, 1000); //add 200 so it's not so low
   }
}
