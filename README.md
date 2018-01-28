# LED-Matrix-DS1307-r2
This program combines an Arduino Uno, a HUB75 32x16 LED Matrix, and a DS1307 RTC from Adafruit to make a clock for the workshop.

The hardest part for me was to create a custom font to fit all the digits to read the time.  I ended up creating bitmaps
of 3x9 pixels.  These are stored in program memory via PROGMEM, though I'm not sure I've done that in the most effective way.


[
![led-clock-ds1307](https://user-images.githubusercontent.com/16627981/35477965-6a1f0e46-039e-11e8-92c3-06fae1490826.JPG)
](url)
