//www.elegoo.com
//2016.12.09
// Original code supplied by Dr. Derickson
// Edited by Drew Miller

//This program uses the joystick to control the color of the multicolor LED
//Connect pin 3 to blue LED pin of the multicolor LED through a 220-330 ohm resistor to GND
//Connect pin 5 to blue LED pin of the multicolor LED through a 220-330 ohm resistor to GND
//Connect pin 5 to blue LED pin of the multicolor LED through a 220-330 ohm resistor to GND
//connect cathode of multicolor LED to GND
//connect joystick +5V to +5V of the arduino
//connect joystick GND to GND of arduino
//connect joystick VRx to A0 on arduino
//connect joystick VRy to A1 on arduino
//connect joystick SW to pin 2 of arduino

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output

// Define Pins
#define BLUE 3
#define GREEN 5
#define RED 6

// Define variables
int redValue;
int greenValue;
int blueValue;
int a;  //value of x axis joystick
int b;  //value of y axis joystick

void setup() {
  pinMode(SW_pin, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(SW_pin, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  Serial.begin(9600);
  
}

void loop() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  a=analogRead(X_pin)/4;
  b=analogRead(Y_pin)/4;
  analogWrite(RED,(int)((255-(float)a)*(1-((float)b/255))));
  analogWrite(GREEN,(int)((float)b*(1-((float)a/255))));
  analogWrite(BLUE,(int)((float)a*(1-((float)b/255))));
  delay(50);
  
}
