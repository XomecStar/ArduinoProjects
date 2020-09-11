/*
    Temperature.ino
    2020 Copyright (c) XomecStar. All rights reserved.

    Author:XomecStar
    2020-09-05

    Temperature monitoring

    This program lets you check the current temperature in the area you are at.

    It has 5 different states:

    State #1 or the idle state, witch is the state where the temperature is inside of normal conditions. The idle state also has a LEDlight connected to it witch blinks every time the screens gets a measurement input.


    State #2 or the High temperature state, is when the temperature reaches 30°C, you will get an alert on the screen telling you that temperature level is high and the LED light will start to blink.


    State #3 or the Critical High temperature state, is when the temperature reaches 40°C, you will get an alert on the screen telling you that temperature level is critical high and the LED light will start to blink.


    State #4 or the Low tempertature state, is when the temperature reaches 20°C, you will get an alert on the screen telling you that temperature level is low and the LED light will start to blink.


    State #5 or the Critical Low temperature state, is when the temperature reaches below 15°C, you will get an alert on the screen telling you that temperature level is critical low and the LED light will start to blink more frequently.

    NOTE!! THE TEMPERATURE LIMITS CAN BE CHANGED TO WHAT EVER YOU LIKE! :)

    ENJOY THE PROGRAM!

*/


#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>
const int B = 4275; // B value of the thermistor
const int R0 = 100000; // R0 = 100K
const int pinTempSensor = A0; // Crove - Temperature Sensor connect to A0
const int ledPin = 2; // Led indicator

rgb_lcd lcd;
//Feel free to change the color values to match what you like. highest number is 250.
const int colorR = 100;
const int colorG = 100;
const int colorB = 100;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  lcd.setRGB(colorR, colorG, colorB);
 digitalWrite(2, HIGH);

  //Prints a message to the display
  lcd.print("Initialzing..");
  delay(3000);

  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //buttonState = digitalRead(buttonPin);
  int a = analogRead(pinTempSensor);
  float R = 1023.0 / a - 1.0;
  R = R0 * R;

  float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;
  digitalWrite(2, HIGH); // Light blink at with the screens refresh time
  delay(20);
  digitalWrite(2, LOW);
  delay(20);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current Temp:");
  lcd.setCursor(0, 1);
  //Print the number of seconds since reset:
  lcd.print(temperature); // displays the temperature collected from the sensor
  delay(1000);


  if (temperature > 40) {
    //When temp reaches 40 or above the following alert sequens will happen
    digitalWrite(2, HIGH);
    delay(40);
    digitalWrite(2, LOW);
    delay(40);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp Alert!");
    lcd.setCursor(0, 1);
    lcd.print("Temp Level Critical!");
    delay(1000);
  }

  else if (temperature > 30) {
    //When temp reaches 30 or above the following alert sequens will happen
    digitalWrite(2, HIGH);
    delay(150);
    digitalWrite(2, LOW);
    delay(50);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp Alert!");
    lcd.setCursor(0, 1);
    lcd.print("Temp Level High!");
    delay(1000);
  }

  if (temperature < 20) {
    //When temp reaches 20 or below the following alert sequens will happen
    /*Servo1.write(5);
      delay(500);
      Servo1.write(45);
      delay(1000);
      //Servo1.write(90);
      //delay(1500);
      Servo1.write(180);
      delay(2000);*/
    digitalWrite(2, HIGH);
    delay(400);
    digitalWrite(2, LOW);
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp Alert!");
    lcd.setCursor(0, 1);
    lcd.print("Temp Level Low!");
    delay(1000);
  }

  else if (temperature < 15) {
    //When temp reaches 15 or below the following alert sequens will happen
    /*Servo1.write(45);
      delay(500);
      Servo1.write(180);
      delay(500);*/
    digitalWrite(2, HIGH);
    delay(40);
    digitalWrite(2, LOW);
    delay(40);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp Warning!!");
    lcd.setCursor(0, 1);
    lcd.print("Temp Level Critical!!");
    delay(1000);
  }

}

/******************************************************************************************************************************************
        END OF FILE
 ******************************************************************************************************************************************/
