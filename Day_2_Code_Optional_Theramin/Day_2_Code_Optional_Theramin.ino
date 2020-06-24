#include <SR04.h> //you'll need this library

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

