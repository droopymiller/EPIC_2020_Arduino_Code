// Connect push button to a pullup resistor and GND (follow Day 2 instructions)
// Connect node with pullup resistor and push button to Arduino pin 2

// Expected Behavior
// When button is held, the LED on the Arduino is on
// When button is not held, LED on the Arduino is off
// This tests the functionality of button subassembly


#define BUTTON_PIN  2
#define LED_PIN     13

void setup(){
    pinMode(LED_PIN, OUTPUT);   // Set LED pin to ouput
    pinMode(BUTTON_PIN, INPUT); // Set button pin to input
}

void loop(){
    if( digitalRead(BUTTON_PIN) ){      // If button is not pressed
        digitalWrite(LED_PIN, LOW);     // Turn LED off
    }
    else{                               // If button is pressed
        digitalWrite(LED_PIN, HIGH);    // Turn LED on
    }
}
