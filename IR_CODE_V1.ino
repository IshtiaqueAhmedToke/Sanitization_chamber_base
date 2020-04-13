// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C

#include <Wire.h> // library for I2C communication
#include <LiquidCrystal_I2C.h> // library for LCD
#define RELAY_ON 0  //relay state on
#define RELAY_OFF 1 //relay state off
#define RELAY_1 4  //relay connected to pin 4

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.

const int buttonPin = 2; //button conncected to pin 2
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

int sensorpin = 0;                 // analog pin used to connect the sharp sensor
int val = 0;                 // variable to store the values from sensor(initially zero)

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to


int sensorValue = 0;        // value read from the pot
int delayValue = 0;        // value output to the PWM (analog out)

int timeDelay =0 ;

void setup()
{

    lcd.init();  //lcd
    lcd.backlight(); //lcd

  pinMode(RELAY_1,OUTPUT);  //relay output
  digitalWrite (RELAY_1,RELAY_OFF);  //relay off by default

  Serial.begin(9600);


}

void loop()
{

  timeDelay = delayValue/1000; //coverts milliseconds to seconds


  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {

   lcd.setCursor(0,0);
   lcd.print("Time Delay ");
   lcd.print(timeDelay);
   lcd.print(" Seconds");
   delay(6000);
   lcd.clear();
  }
  else{
    lcd.print("READY TO SANITIZE");
  }


   // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  delayValue = map(sensorValue, 0, 1023, 15000, 25000);//15 seconds to 25 seconds






  val = analogRead(sensorpin);       // reads the value of the sharp sensor


lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
lcd.print("READY TO SANITIZE");

if(val>=270)
   {
     lcd.clear();
     delay(2500);  //delay of 2.5 seconds to let the person get inside the chamber
      digitalWrite(RELAY_1,RELAY_ON);

    lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("SANITIZING");
    delay(delayValue);     //delay value based on the potentiometer setting based on user input
    lcd.clear();
    digitalWrite(RELAY_1,RELAY_OFF);
    delay(100);
    lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("READY TO SANITIZE");
}




}
