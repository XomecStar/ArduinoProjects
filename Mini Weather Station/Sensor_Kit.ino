/*
Project created by XomecStar
   2020 Copyright (c) XomecStar. All rights reserved.
   
   Author:XomecStar
   2020-12-12
   
   This is a mini weather station! It checks current humidity level temperature(Celcius and Fahreinheit) and current light exposour using a Light sensor.
   
   NOTE!! This program is used with a OLED 0.96" Display! If you wish to use a larger OLED display, then you must modify the code! 
   Also if you wish to use a LCD display instead of the OLED display, you must modify the code to work!!

This project can be used for your own use and can be modified the way you want! 
*/
#include "DHT.h"
#define DHT11Pin 2
#define DHTType DHT11
//OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

DHT HT(DHT11Pin, DHTType);
float humi;
float tempC;
float tempF;

//OLED define
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define button 4

const int ledPin = 6;
const int light_sensor = A3;
int button_state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(button, INPUT);
  //For DHT11
  HT.begin();
  //For OLED I2C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display(); //Display logo
  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  display.clearDisplay();

}

void loop() {
  button_state = digitalRead(button);
  delay(1000);
  int raw_light = analogRead(light_sensor);
  int light = map(raw_light, 0, 800, 0, 100);
  statusScreen();
  warnings();



  if (button_state != LOW) {
    //Display Light Expo level from light sensor
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Light lvl: ");
    display.setCursor(0, 20);
    display.print(light);
    display.println("%");
    display.display();
    Serial.println("Button Pressed");
    delay(1000);
  }


}
void warnings() {
  int raw_light = analogRead(light_sensor);
  int light = map(raw_light, 0, 800, 0, 100);
  if (humi >= 40) {
    warningFlash();
  } else {
    if (humi <= 30) {
      warningFlashX2();
    } else {
      if (humi <= 30 && tempC <= 15 && tempF <= 59) {
        dangerFlash();
      } else {
        if (light < 5) {
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.print("Power loss?");
          display.setCursor(0, 30);
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 25);
          display.println("Light: ");
          display.print(light);
          display.print("%");
          display.display();
          delay(100000);
        } else {
          statusScreen();
        }
      }

    }
  }
}

void statusScreen() {
  int raw_light = analogRead(light_sensor);
  int light = map(raw_light, 0, 800, 0, 100);
  humi = HT.readHumidity();
  tempC = HT.readTemperature();
  tempF = HT.readTemperature(true);


  Serial.print("Humidity:");
  Serial.print(humi, 0);
  Serial.print("%");
  Serial.print(" Temperature:");
  Serial.print(tempC, 1);
  Serial.print("C ~ ");
  Serial.print(tempF, 1);
  Serial.println("F");
  Serial.print("Light level: ");
  Serial.println(light);

  display.clearDisplay();
  oledDisplayHeader();


  oledDisplay(3, 5, 28, humi, "%");
  oledDisplay(2, 70, 16, tempC, "C");
  oledDisplay(2, 70, 44, tempF, "F");

  display.display();


}
void warningFlash() {
  digitalWrite(6, HIGH);
  delay(2000);
  digitalWrite(6, LOW);
  delay(2500);
}
void warningFlashX2() {
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, LOW);
  delay(450);
}

void dangerFlash() {
  digitalWrite(6, HIGH);
  delay(80);
  digitalWrite(6, LOW);
  delay(80);
}

void oledDisplayHeader() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Humidity");
  display.setCursor(60, 0);
  display.print("Temperature");
}
void oledDisplay(int size, int x, int y, float value, String unit) {
  int charLen = 12;
  int xo = x + charLen * 3.2;
  int xunit = x + charLen * 3.6;
  int xval = x;
  display.setTextSize(size);
  display.setTextColor(WHITE);

  if (unit == "%") {
    display.setCursor(x, y);
    display.print(value, 0);
    display.print(unit);
  } else {
    if (value > 99) {
      xval = x;
    } else {
      xval = x + charLen;
    }
    display.setCursor(xval, y);
    display.print(value, 0);
    display.drawCircle(xo, y + 2, 2, WHITE); // print degree symbols (  )
    display.setCursor(xunit, y);
    display.print(unit);
  }

}
/******************************************************************************************************************************************
        END OF FILE
 ******************************************************************************************************************************************/
