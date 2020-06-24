// Prerequisite: Motor and L293D chip must already be wired to the Arduino

// This code can be used to test how well your fan blows your sailboat
// The fan will spin when the button is pressed.
// The fan direction and speed can be adjusted in the code below.
// Look for comments indicating where to adjust these.

#define ENABLE  5
#define DIRA    3
#define DIRB    4

#define BUTTON  2

void setup(){
    // Set pin directions
    pinMode(ENABLE, OUTPUT);
    pinMode(DIRA, OUTPUT);
    pinMode(DIRB, OUTPUT);
    pinMode(BUTTON, INPUT);
}

void loop(){
    // Change direction by swapping "DIRA" and "DIRB" in the following two lines
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
    if( digitalRead(BUTTON) ){      // If button is not pressed
        digitalWrite(ENABLE, LOW);  // Turn fan off
    }
    else{                           // If button is pressed
        analogWrite(ENABLE, 255);   // Turn fan and set speed
                                    // Speed can be set between 0-255
                                    // 0 is the slowest and 255 is the fastest
    }
}
