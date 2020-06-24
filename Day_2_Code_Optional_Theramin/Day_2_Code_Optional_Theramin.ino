#include <SR04.h>       // Ultrasonic sensor libraru

#define TRIG_PIN 12     // Using pins 11+12
#define ECHO_PIN 11
#define BUZZER   8      // Pin 8 for buzzer

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);        // initialize our ultrasonic sensor
long dist;                                  //our distance variable

void setup() {
  Serial.begin(9600);               //debugging purposes
  pinMode(BUZZER, OUTPUT);
}

void loop() {
   dist = sr04.Distance();          //get distance
   Serial.println(dist);            //print to serial for debugging
   //delay(100); you'll need this if you use the serial monitor so you don't get overwhelmed
   if (not (dist > 1000)) {         // so we don't get annoying high-pitch squeacks if we get a bad reading
    tone(BUZZER, dist*10 + 200, 1000);      // add 200 so it's not so low
   }
}
