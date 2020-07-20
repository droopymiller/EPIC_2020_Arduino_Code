// Original Code supplied by Elegoo.
// Major tweaks and documentation by Gerome Cacho

/*

Directions:
- Open serial monitor (Make sure Baudrate is at 9600)
- Type something into serial monitor
- Watch it show up on the LCD screen
- Use the potentiometer to adjust the contrast of the LCD screen
- Old messages gets pushed down until out of the LCD screen altogether

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
  */
  
// include the library code:
#include <LiquidCrystal.h>

#define Chromebook 1;
#define Other 2;


LiquidCrystal lcd(7, 8, 9, 10, 11, 12);       // initialize the library with the numbers of the interface pins for data
String first_line = "                 ";      // Creates variables for first and second line
String second_line;
int adjust = Other;

void setup() {
  lcd.begin(16, 2);                           // set up the LCD's number of columns and rows:
  lcd.clear();                                // Clears the LCD initially
  Serial.begin(9600);                         // Initializes Serial Monitor
}

void loop() 
{
  lcd.setCursor(0, 0);                        // set the cursor to column 0, line 0
  if (Serial.available())                     // If we get something from the serial monitor
  {
    lcd.clear();                                // Wipe the LCD clean
    second_line = first_line;                   // Swap line texts
    first_line = Serial.readString();           // Read the message sent through the Serial Monitor
    Serial.print(first_line);                   // Echos the message to the serial monitor
    for (int index = 0; index < 16; index++){   // Prints the message of first_line character by character on the LCD
      lcd.setCursor(index,0);                     // Placement of the Cursor. Priming it to write
      char character = first_line[index];
      lcd.write(character);                       // Writes the character to the LCD screen
      if (index == first_line.length()-adjust){   // Change based on OS. See #defines above
        break;                                      // Used to hard-code against long messages
        }
    }
    for (int index = 0; index < 16; index++){   // Same thing as before, but for the second line
      lcd.setCursor(index,1);
      char character = second_line[index];
      lcd.write(character);
      if (index == second_line.length()-adjust){   
        break;
        }
    }
  }
}
