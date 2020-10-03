#include <Arduino.h>
#include <U8g2lib.h>
#include <U8x8lib.h>
#include <SPI.h>
#include <Wire.h>
#include <NewPing.h>
#define ECHOPIN 3// Pin to receive echo pulse 12
#define TRIGPIN 2// Pin to send trigger pulse 11
#define MAX_DISTANCE 200

float duration; // Stores HC-SR04 pulse duration value
int distance; // Stores calculated distance in cm

int iterations = 5;

NewPing sonar(TRIGPIN, ECHOPIN, MAX_DISTANCE);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //********************HW is faster than SW*************************************
//U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
//U8G2_SSD1322_NHD_256X64_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 13, /* reset=*/ 12);  // Enable U8G2_16BIT in u8g2.h
//U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 5, /* dc=*/ 13, /* reset=*/ 12);  // Enable U8G2_16BIT in u8g2.h******HW is faster than SW********


void setup()
{
  Serial.begin(9600);
  u8g2.begin();
}

void loop()
{

  duration = sonar.ping_median(iterations);
  distance = (duration / 2) * 0.0343;

  if (distance < MAX_DISTANCE && distance >= 100 ) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_inb33_mn   );  //Best bold number font for ssd1306 128 x 32
      u8g2.setCursor(10, 32);
      u8g2.print(distance);
      u8g2.setFont(u8g2_font_bitcasual_tr   );
      u8g2.setCursor(100, 20);              // Best center text for 128 x 32
      u8g2.print("C M");
    } while ( u8g2.nextPage() );
    delay(10);
  }

  else if (distance < 100 && distance >= 50 ) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_inb33_mn   );  //Best bold number font for ssd1306 128 x 32
      //u8g2.setFont(u8g2_font_fub42_tn );  //Best bold number font for ssd1306 128 x 64
      u8g2.setCursor(30, 32);
      u8g2.print(distance);
      u8g2.setFont(u8g2_font_bitcasual_tr   );
      u8g2.setCursor(100, 20);               // Best center text for 128 x 64
      u8g2.print("C M");
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawGlyph(5, 25, 0x0036);  /* dec 9731/hex 2603 Snowman */
    } while ( u8g2.nextPage() );
    delay(10);
  }

  else if (distance < 50 && distance >= 40 ) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_inb33_mn   );  //Best bold number font for ssd1306 128 x 32
      //u8g2.setFont(u8g2_font_fub42_tn );  //Best bold number font for ssd1306 128 x 64
      u8g2.setCursor(30, 32);
      u8g2.print(distance);
      u8g2.setFont(u8g2_font_bitcasual_tr   );
      u8g2.setCursor(100, 20);               // Best center text for 128 x 64
      u8g2.print("C M");
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawGlyph(5, 25, 0x0034);  /* dec 9731/hex 2603 Snowman */
    } while ( u8g2.nextPage() );
    delay(10);
  }

    else if (distance < 40 && distance >= 30 ) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_inb33_mn   );  //Best bold number font for ssd1306 128 x 32
      //u8g2.setFont(u8g2_font_fub42_tn );  //Best bold number font for ssd1306 128 x 64
      u8g2.setCursor(30, 32);
      u8g2.print(distance);
      u8g2.setFont(u8g2_font_bitcasual_tr   );
      u8g2.setCursor(100, 20);               // Best center text for 128 x 64
      u8g2.print("C M");
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawGlyph(5, 25, 0x0035);  /* dec 9731/hex 2603 Snowman */
    } while ( u8g2.nextPage() );
    delay(10);
  }

  else if (distance < 30 && distance >= 20 ) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_inb33_mn   );  //Best bold number font for ssd1306 128 x 32
      //u8g2.setFont(u8g2_font_fub42_tn );  //Best bold number font for ssd1306 128 x 64
      u8g2.setCursor(30, 32);
      u8g2.print(distance);
      u8g2.setFont(u8g2_font_bitcasual_tr   );
      u8g2.setCursor(100, 20);               // Best center text for 128 x 64
      u8g2.print("C M");
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawGlyph(5, 25, 0x0029);  /* dec 9731/hex 2603 Snowman */
    } while ( u8g2.nextPage() );
    delay(10);
  }

  else {
    u8g2.clear();
  }
}

//*******************************************************/
// إطفاء الشاشة عندما تكون المسافة أكبر من رقم محدد
//حتى لا تبقى الشاشة في السيارة تعمل دائماً
/*Description: Activates (is_enable = 1) or disables (is_enable = 0)
  the power save mode of the display. With activated power save mode,
  nothing will be visible on the display. The content of the RAM of the display is not changed.
  This procedure is also called from begin.
  if (distance <= 20) {
  u8g2.setPowerSave(1);
  }
  else {
  u8g2.setPowerSave(0);
  }
  //******************************************************/
