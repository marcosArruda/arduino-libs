/*
  LiquidCrystal Library - display() and noDisplay()
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD and uses the 
 display() and noDisplay() functions to turn on and off
 the display.
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe 
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/LiquidCrystalDisplay

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(44, 45, 46, 47, 48, 49);

// make some custom characters:
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

byte ohm[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01010,
  0b11011
};

byte degrees1[8] = {
  B01000,
  B10100,
  B01000,
  B00011,
  B00100,
  B00100,
  B00011,
  B00000
};

byte arrowRight[8] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
  B00000
};

byte arrowLeft[8] = {
  B00000,
  B00100,
  B01000,
  B11111,
  B01000,
  B00100,
  B00000,
  B00000
};

byte arrowUp[8] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000
};
uint8_t cs[8] = {0, 1, 2, 3, 4, 5, 6, 7};
int cnt = 0;

void setup() {
  //lcd.createChar(0, heart);
  lcd.createChar(0, smiley);
  lcd.createChar(1, frownie);
  lcd.createChar(2, armsDown);
  lcd.createChar(3, armsUp);
  lcd.createChar(4, ohm);
  lcd.createChar(5, degrees1);
  lcd.createChar(6, arrowUp);
  lcd.createChar(7, arrowLeft);
  lcd.begin(16, 2);
  lcd.print("Waldemar!");
  //pinMode(8, OUTPUT);
}

void loop() {
  if(cnt > 7) cnt = 0;
  // Turn on the display:
  lcd.setCursor(cnt, 1);
  lcd.write(cs[cnt++]);
  lcd.display();
}

void music(){
  int C = 262, D = 294, E = 330, F = 349, G = 392, A = 440, B = 523;
  int P = 0;
  int i;
  int ode[] = {
    E,E,F,G,G,F,E,D,C,C,D,E,E,D,P,D,P,
    E,E,F,G,G,F,E,D,C,C,D,E,D,C,P,C,P,
    D,D,E,C,D,E,P,F,E,C,D,E,P,F,E,D,C,D,P,
    E,E,D,G,G,F,E,D,C,C,D,E,D,C,P,C   };
  int tempo[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1.5,1,.5,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1.5,1,.5,1,1,
    1,1,1,1,1,1,.5,1,1,1,1,1,.5,1,1.5,1,.5,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1.5,.125,1,1  };
  for(i=0;i<sizeof(ode)/2;i++) {
    if(ode[i] != 0) tone(8,ode[i]); 
    else noTone(8);
    delay(tempo[i] * 500);
    noTone(8);
  }
  noTone(8);
  delay(10000);
}

