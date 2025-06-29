// PROJECT DETAILS;

// AUTHOR: IMRE ABEL
// DATE: 6/29/2025

// THE GOAL OF THIS PROJECT IS TO UTILIZE A 3-6V MOTOR IN CONJUNCTION WITH THE LCD1602, THERMISTOR, L293D, POTENTIOMETER, POWERSUPPLY MODULE, AND RED AND GREEN LEDS TO CREATE A BASIC AUTO COOLING SYSTEM 
// THAT ACTIVATES THE MOTOR AND CORRECT LED WHEN TEMP IS HIGH AND VICE VERSA DURING NORMAL TEMPS.

// BREIF DESCRIPTION OF SETUP BELOW (FIRSTLY AQUIRE ALL REQUIRED SUPPLYS LISTED IN README):

// 1. ATTACH LCD1602, AND POTENTIOMETER TO BREADBOARD OF CHOICE, CONNECT THE WIRES IN THE WIRING DIAGRAM LISTED IN README
// 2. ATTACH GREEN AND RED LEDS WITH 220 OHMS RESISTORS AND GROUND WIRES IN LOCATION OF CHOICE
// 3. ATTACH POWERSUPPLY MODULE AND L293D MOTOR CONTROL MODULE WITH CORRECT WIRING 

// README FOR MORE DETAILED DESCRIPTION

// INCLUDE LIBRARY FOR LCD1602 AND SETUP TO CORRESPONDING PINS PLUGGED INTO ARUDINO BOARD
#include <LiquidCrystal.h>
int tempPin = 0;
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// DEFINE WHERE ALL NECCESARY PINS ARE PLUGGED IN TO ARDUINO BOARD
#define RED_PIN 2
#define GREEN_PIN 4

// THESE ARE FOR MOTOR CONTROL
#define ENABLE 5
#define DIRA 3
#define DIRB 13

// SETUP MOTOR, LEDS, AND SERIAL OUTPUT
void setup()
{
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  lcd.begin(16, 2);
}

// MAIN CODE IS HERE
void loop()
{
  // START OF WITH SETTING UP TEMP CALCULATIONS FOR EITHER F OR C 
  int tempReading = analogRead(tempPin);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit

// IF STATEMENT TO DETERMINE WHEN THE FAN WILL ACTIVATE BASED ON DESIRED TEMPERATURE AND WHAT LED YOU WANT TO ACTIVATE USALLY RED TO INDICATE HIGH TEMP BUT YOU DO YOU GREEN CAN BE CHOSEN ASWELL AS A FAN ON INDICATOR.
  if ( tempF > 77.20){
      analogWrite(ENABLE, 250); // 250 FOR FAN SPEED MAX IS 255
     digitalWrite(DIRA, HIGH);
     digitalWrite(DIRB, LOW);
     
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
    
    lcd.setCursor(0,0); // SETUP WHERE YOU WANT LED TO START PRINTING BASED IN LED SIZE OR DESIRED OUTPUT LOCATION
    lcd.print("TEMP-HIGH       ");
    lcd.setCursor(0,1);
    lcd.print("FAN-ON");
    lcd.setCursor(7,1);
    lcd.print(tempF);
    lcd.print("F");
  }

  
  else{
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */
  // THIS IS THE PART WHERE THE TEMPERATURE IS WITHIN THE SET TEMPERATURE SO FAN IS NOT ACTIVE AND GREEN LED IS ON WHILE TEMPERATURE IN F IS DIPLAYED IN REAL TIME 
  digitalWrite(DIRA, LOW);
digitalWrite(DIRB, LOW);
analogWrite(ENABLE, 0); 
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp         F  ");
  // Display Temperature in F
  //lcd.print("Temp         F  ");
  lcd.setCursor(6, 0);
  // Display Temperature in C
  lcd.print(tempF);
  // Display Temperature in F
  //lcd.print(tempF);
  delay(500);
}
}
 // THANKS FOR VIEWING LOOK FORWARD TO MORE ADVANCED PROJECTS
