// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
//#include "DHT.h" // dht22
#include <Wire.h>
#include "RTClib.h"
//#include <Fonts/FreeMono12pt7b.h> // don't need fonts for just a clock

#define DHTTYPE DHT22

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

byte LEDBRIGHTNESS = 32; // 0-255
int previousMinute = -1;
char buffer[4];

// declare rtc
RTC_DS1307 rtc;

// CUSTOM BITMAPS FOR NUMBERS
//3x9 number digit font bitmaps
byte one[]= {B01000000,
             B11000000,
             B01000000,
             B01000000,
             B01000000,
             B01000000,
             B01000000,
             B01000000,
             B11100000};

byte two[]= {B11100000,
             B00100000,
             B00100000,
             B00100000,
             B11100000,
             B10000000,
             B10000000,
             B10000000,
             B11100000};

byte three[]= {B11100000,
               B00100000,
               B00100000,
               B00100000,
               B11100000,
               B00100000,
               B00100000,
               B00100000,
               B11100000};

byte four[]= {B10100000,
              B10100000,
              B10100000,
              B10100000,
              B11100000,
              B00100000,
              B00100000,
              B00100000,
              B00100000};

byte five[]= {B11100000,
              B10000000,
              B10000000,
              B10000000,
              B11100000,
              B00100000,
              B00100000,
              B00100000,
              B11100000};


byte six[]=  {B11100000,
              B10000000,
              B10000000,
              B10000000,
              B11100000,
              B10100000,
              B10100000,
              B10100000,
              B11100000};

byte seven[]={B11100000,
              B00100000,
              B00100000,
              B00100000,
              B00100000,
              B00100000,
              B00100000,
              B00100000,
              B00100000};

byte eight[]={B11100000,
              B10100000,
              B10100000,
              B10100000,
              B11100000,
              B10100000,
              B10100000,
              B10100000,
              B11100000};

byte nine[]={ B11100000,
              B10100000,
              B10100000,
              B10100000,
              B11100000,
              B00100000,
              B00100000,
              B00100000,
              B00100000};

byte zero[]={ B11100000,
              B10100000,
              B10100000,
              B10100000,
              B10100000,
              B10100000,
              B10100000,
              B10100000,
              B11100000};

byte colon[]={B00000000,
              B01000000,
              B01000000,
              B00000000,
              B00000000,
              B01000000,
              B01000000,
              B00000000,
              B00000000};

char *noArray[] = {zero, one, two, three, four, five, six, seven, eight, nine, colon};
const char* const string_table[] PROGMEM = {zero, one, two, three, four, five, six, seven, eight, nine, colon};

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 test!");
//  dht.begin();
  matrix.begin();


  // clock start
  if (! rtc.begin()){
    Serial.println("couldn't find RTC");
    while(1);
  }

  if (! rtc.isrunning()){
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7)); 
  delay(500);
  
  matrix.setCursor(8, 14);   // start at top left, with one pixel of spacing
//  matrix.setFont(&FreeMono12pt7b);
  matrix.setTextColor(matrix.Color333(6,4,0));
  matrix.print('Hello');
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

String convertIntTo2DigitString(int i)  {
  String s = String(i);
  if (i < 10)  {
    s = '0'+s;
  }
  return s;
}

void loop() {
  DateTime now = rtc.now();
  int secs;
  int currentMinute = now.minute();
  int currentHour = now.hour();

  if (currentMinute != previousMinute) {
    Serial.println(currentMinute);
    previousMinute = currentMinute;
    String min = convertIntTo2DigitString(currentMinute);
    String hour = convertIntTo2DigitString(currentHour);
    
//    matrix.setCursor(0,15);
    matrix.setTextSize(1);
    matrix.fillScreen(matrix.Color333(0,0,0));
    matrix.setTextColor(matrix.Color333(4,2,0));
// Try to print out bitmaps of minutes
    matrix.drawBitmap(5, 3, (byte*)noArray[(int)hour[0]-'0'], 3, 9, matrix.Color333(4,1,0));
    matrix.drawBitmap(10, 3, (byte*)noArray[(int)hour[1]-'0'], 3, 9, matrix.Color333(4,1,0));
    matrix.drawBitmap(15, 3, (byte*)noArray[10], 3, 9, matrix.Color333(3,1,0));
    matrix.drawBitmap(19, 3, (byte*)noArray[(int)min[0]-'0'], 3, 9, matrix.Color333(4,1,0));
    matrix.drawBitmap(24, 3, (byte*)noArray[(int)min[1]-'0'], 3, 9, matrix.Color333(4,1,0));
    delay(5000);
  }
  
}
