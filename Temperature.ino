#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>
#include <Servo.h>
const int B = 4275; // B value of the thermistor
const int R0 = 100000; // R0 = 100K
const int pinTempSensor = A0; // Crove - Temperature Sensor connect to A0
const int Buzz = A1; // Buzzzer
const int buttonPin = 8; // Button
const int ledPin = 2; // Led indicator
const int servoPin = 3; // Servo Pin for Analog Servo

rgb_lcd lcd;

const int colorR = 250;
const int colorG = 250;
const int colorB = 250;

int buttonState = 0;
//Servo object
Servo Servo1;

void setup() {
  // put your setup code here, to run once:
  Servo1.attach(servoPin);
  lcd.begin(16, 2);

  lcd.setRGB(colorR, colorG, colorB);

  //Prints a message to the display
  lcd.print("Initialzing..");
  delay(3000);

  Serial.begin(9600);
  pinMode(Buzz, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  int a = analogRead(pinTempSensor);
  float R = 1023.0 / a - 1.0;
  R = R0 * R;

  float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current Temp:");
  lcd.setCursor(0, 1);
  //Print the number of seconds since reset:
  lcd.print(temperature);
  delay(1000);

  /*if (temperature > 25) {
    digitalWrite(Buzz, HIGH);
    tone(Buzz, 813, 750);
    delay(1000);
    digitalWrite(Buzz, LOW);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp Alert!");
    lcd.setCursor(0, 1);
    lcd.print("Temp Level High!");
    delay(1000);

    AlertReset();
  }*/

  if (temperature > 25) {
    digitalWrite(2, HIGH);
    delay(750);
    digitalWrite(2, LOW);
    delay(500);
    Servo1.write(0);
    delay(1000);
    Servo1.write(180);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp Alert!");
    lcd.setCursor(0, 1);
    lcd.print("Temp Level High!");
    delay(1000);
  }

}

void AlertReset() {
  if (buttonState == HIGH) {
    digitalWrite(Buzz, LOW);
    delay(5);
    digitalWrite(Buzz, LOW);
    delay(5);
    digitalWrite(Buzz, LOW);
    delay(5);
    digitalWrite(Buzz, LOW);
    delay(5);
  }
  else {
    loop();
  }
}
