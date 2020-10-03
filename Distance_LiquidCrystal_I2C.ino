#include <Wire.h>
#include <Arduino.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>      //https://github.com/modarsoos/LiquidCrystal_I2C
#include <NewPing.h>
#define ECHOPIN 12// Pin to receive echo pulse 12
#define TRIGPIN 13// Pin to send trigger pulse 11
#define MAX_DISTANCE 200

float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
//float soundsp;  // Stores calculated speed of sound in M/S
//float soundcm;  // Stores calculated speed of sound in cm/ms
int iterations = 5;
int buzzer = 3;
int ledPinR = 5;
int ledPinG = 6;
int ledPinB = 9;
DS3231  rtc(SDA, SCL);
NewPing sonar(TRIGPIN, ECHOPIN, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  rtc.begin();
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print(rtc.getDateStr());
  lcd.setCursor(4, 1);
  lcd.print(rtc.getTemp());
  lcd.setCursor(11, 1);
  lcd.print("C");
  delay(2000);
}


void loop()
{
  duration = sonar.ping_median(iterations);
  distance = (duration / 2) * 0.0343;

  int rateBuzz = map(distance, 21 , MAX_DISTANCE , 50 , 400);
  int rateLedR = map(distance, 21 , 50 , 1 , 20);
  int rateLedG = map(distance, 51 , 75 , 20 , 40);

  if (distance < MAX_DISTANCE && distance >= 100 ) {
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.setCursor(5, 1);
    lcd.print(distance);
    lcd.setCursor(13, 1);
    lcd.print("CM");

    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinB, LOW);

    for (int r = 50 ; r < 256 ; r = r + 50) {
      analogWrite(ledPinG, r);
      delay(rateLedG);
    }
    for (int r = 255 ; r >= 50 ; r = r - 50) {
      analogWrite(ledPinG, r);
      delay(rateLedG);
    }
  }
  else if (distance < 100 && distance >= 20 ) {
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.setCursor(5, 1);
    lcd.print(distance);
    lcd.setCursor(13, 1);
    lcd.print("CM");

    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinB, LOW);

    for (int r = 0 ; r < 256 ; r = r + 50) {
      analogWrite(ledPinR, r);
      delay(rateLedR);
    }
    for (int r = 255 ; r >= 0 ; r = r - 50) {
      analogWrite(ledPinR, r);
      delay(rateLedR);
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print(rtc.getDateStr());
    lcd.setCursor(4, 1);
    lcd.print(rtc.getTimeStr());

    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, LOW);

    if (rtc.getTimeStr() < 12) {
      lcd.setCursor(14, 1);
      lcd.print("AM");
    }
    else {
      lcd.setCursor(14, 1);
      lcd.print("PM");
    }
    delay(1000);
  }
  delay(10);
}
