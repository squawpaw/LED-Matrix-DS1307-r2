# LED-Matrix-DS1307-r2
This program combines an Arduino Uno, a HUB75 32x16 LED Matrix, and a DS107 RTC from Adafruit to make a clock for the workshop.

The hardest part for me was to create a custom font to fit all the digits to read the time.  I ended up creating bitmaps
of 3x9 pixels.  These are stored in program memory via PROGMEM, though I'm not sure I've done that in the most effective way.


