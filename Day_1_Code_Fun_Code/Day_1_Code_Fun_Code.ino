// Code obtained from online.
// Altered and documented by Gerome Cacho.
// Same wiring as the Birthday code
// PLEASE DO NOT SPOIL THE SONG FOR OTHER PEOPLE. KEEP IT A SURPRISE =)

int c3 = 131;
int cS3 = 139;
int d3 = 147;
int dS3 = 156;
int e3 = 165;
int f3 = 175;
int fS3 = 185;
int g3 = 196;
int gS3 = 208;
int a3 = 220;
int aS3 = 233;
int b3 = 247;
int c4 = 261;
int cS4 = 277;
int d4 = 294;
int dS4 = 311;
int e4 = 329;
int f4 = 349;
int fS4 = 370;
int g4 = 391;
int gS4 = 415;
int a4 = 440;
int aS4 = 455;
int b4 = 466;
int c5 = 523;
int cS5 = 554;
int d5 = 587;
int dS5 = 622;
int e5 = 659;
int f5 = 698;
int fS5 = 740;
int g5 = 784;
int gS5 = 830;
int a5 = 880;

int buzzerPin = 8;
int ledPin1 = 9;
int ledPin2 = 10;
int ledPin3 = 11;
int ledPin4 = 12;

int counter = 0;

void setup()
{                             //Setup pin modes
    pinMode(buzzerPin, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
}

void loop()
{
    firstSection();         //Play first section

    secondSection();        //Play second section

    beep(dS3, 250);         //Variant 1
    beep(fS3, 500);
    beep(dS3, 350);
    beep(fS3, 100);
    beep(aS3, 500);
    beep(g3, 375);
    beep(aS3, 100);
    beep(d4, 650);

    delay(500);

    secondSection();        //Repeat second section

    beep(dS3, 250);         //Variant 2
    beep(fS3, 500);
    beep(dS3, 375);
    beep(aS3, 100);
    beep(g3, 500);
    beep(dS3, 375);
    beep(aS3, 100);
    beep(g3, 650);

    delay(5000);            //Wait 5 seconds before running again
}

void beep(int note, int duration)       //Subroutine. Basically a chunk of code that is called many times over that for readability purposes, we took out and placed here.
{
    tone(buzzerPin, note, duration);    //Play tone on buzzerPin
    if(counter % 2 == 0)
    {
        digitalWrite(ledPin1, HIGH);    //Play different LED depending on value of 'counter'
        digitalWrite(ledPin2, HIGH);
        delay(duration);
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
    }
    else
    {
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin4, HIGH);
        delay(duration);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
    }
    noTone(buzzerPin);                  //Stop tone on buzzerPin
    delay(50);
    counter++;                          //Increment counter
}

void firstSection()
{
    beep(g3, 500);
    beep(g3, 500);
    beep(g3, 500);
    beep(dS3, 350);
    beep(aS3, 150);
    beep(g3, 500);
    beep(dS3, 350);
    beep(aS3, 150);
    beep(g3, 650);

    delay(500);

    beep(d4, 500);
    beep(d4, 500);
    beep(d4, 500);
    beep(dS4, 350);
    beep(aS3, 150);
    beep(fS3, 500);
    beep(dS3, 350);
    beep(aS3, 150);
    beep(g3, 650);

    delay(500);
}

void secondSection()
{
    beep(g4, 500);
    beep(g3, 300);
    beep(g3, 150);
    beep(g4, 500);
    beep(fS4, 325);
    beep(dS4, 175);
    beep(e4, 100);
    beep(dS4, 100);
    beep(e4, 250);

    delay(300);

    beep(gS3, 250);
    beep(cS4, 500);
    beep(c4, 325);
    beep(b3, 175);
    beep(aS3, 100);
    beep(a3, 100);
    beep(aS3, 250);

    delay(325);
}
