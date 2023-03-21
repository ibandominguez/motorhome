#ifndef LcdAnimation_h
#define LcdAnimation_h

#include <LiquidCrystal.h>

class LcdAnimation: public LiquidCrystal {
  using LiquidCrystal::LiquidCrystal;

  private:
    int introAnimationIndex = 0;
    byte iconCarTop[8] = { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111 };
    byte iconCarTopFront[8] = { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11110 };
    byte iconCarBottom[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B00101, B00111 };
    byte iconCarBottomFront[8] = { B11000, B11000, B11100, B11111, B11111, B11111, B00000, B00000 };
    byte iconCarBottomMoving[8] = { B11111, B11111, B11111, B11111, B11111, B11010, B00101, B00010 };
    byte iconMale[8] = { B01110, B01110, B01110, B11111, B00100, B01110, B01010, B11011 };
    byte iconFemale[8] = { B01110, B01110, B01110, B11111, B00100, B01110, B11111, B11111 };
    byte iconBaby[8] = { B00000, B00000, B00000, B01110, B01110, B11111, B01110, B01010 };
    byte iconDog[8] = { B00000, B00000, B10100, B11100, B11100, B01000, B11111, B10101 };

  public:
    LcdAnimation(int a, int b, int c, int d, int e, int f) : LiquidCrystal(a, b, c, d, e, f) {
      pinMode(a, OUTPUT);
      pinMode(b, OUTPUT);
      pinMode(c, OUTPUT);
      pinMode(d, OUTPUT);
      pinMode(e, OUTPUT);
      pinMode(f, OUTPUT);
    }

    void setupPWMContrastPin(int pin, int value) {
      pinMode(pin, OUTPUT);
      analogWrite(pin, value);
    }

    void setupIcons() {
      createChar(0, iconCarTop);
      createChar(1, iconCarTopFront);
      createChar(2, iconCarBottom);
      createChar(3, iconCarBottomFront);
      createChar(4, iconMale);
      createChar(5, iconFemale);
      createChar(6, iconBaby);
      createChar(7, iconDog);  
    };

    void toggleIntroAnimation() {
      clear();
      home();

      setCursor(0, 1);
      write("    FIAT FIORINO");

      setCursor(introAnimationIndex, 0);
      write(byte(0));
      setCursor(introAnimationIndex + 1, 0);
      write(byte(0));
      setCursor(introAnimationIndex + 2, 0);
      write(byte(1));
      setCursor(introAnimationIndex, 1);
      write(byte(2));
      setCursor(introAnimationIndex + 1, 1);
      write(byte(2));
      setCursor(introAnimationIndex + 2, 1);
      write(byte(3));
      createChar(2, introAnimationIndex % 2 == 0 ? iconCarBottomMoving : iconCarBottom);

      introAnimationIndex = introAnimationIndex > 12 ? 0 : introAnimationIndex + 1;
    }

    void renderTextAnimated(String text, int x, int y, int speed) {
      setCursor(x, y);
      for (int i = 0; i < text.length(); i++) {
        write(text[i]);
        delay(speed);
      }
    }

    void renderHomeMotorhomeIcon() {
      setCursor(0, 0);
      write(byte(0));
      setCursor(1, 0);
      write(byte(0));
      setCursor(2, 0);
      write(byte(1));
      setCursor(0, 1);
      write(byte(2));
      setCursor(1, 1);
      write(byte(2));
      setCursor(2, 1);
      write(byte(3));
    }

    void playFamilyAnimation() {
      flush();
      clear();
      setCursor(0, 0);
      write(byte(0));
      setCursor(1, 0);
      write(byte(0));
      setCursor(2, 0);
      write(byte(1));
      setCursor(0, 1);
      write(byte(2));
      setCursor(1, 1);
      write(byte(2));
      setCursor(2, 1);
      write(byte(3));
      delay(500);

      renderTextAnimated("FIAT FIORINO", 4, 0, 100);
      delay(500);

      renderTextAnimated("TODOS ARRIBA", 4, 0, 100);
      delay(500);

      setCursor(4, 1);
      write(byte(4));
      renderTextAnimated("IBAN", 12, 1, 100);
      delay(500);

      setCursor(5, 1);
      write(byte(5));
      renderTextAnimated("SONIA", 11, 1, 100);
      delay(500);

      setCursor(6, 1);
      write(byte(6));
      renderTextAnimated("MATEO", 11, 1, 100);
      delay(500);

      setCursor(7, 1);
      write(byte(7));
      renderTextAnimated("ANTONIA", 9, 1, 100);
      renderTextAnimated("       ", 9, 1, 100);
      delay(500);

      renderTextAnimated("AVENTURAS!!!", 4, 0, 100);
      delay(500);

      // Motorhome leaving
      clear();
      setCursor(0, 0);
      write(byte(0));
      setCursor(1, 0);
      write(byte(0));
      setCursor(2, 0);
      write(byte(1));
      setCursor(0, 1);
      write(byte(2));
      setCursor(1, 1);
      write(byte(2));
      setCursor(2, 1);
      write(byte(3));
      delay(500);

      for (int i = 0; i < 16; i++) {
        createChar(2, i % 2 == 0 ? iconCarBottomMoving : iconCarBottom);
        scrollDisplayRight();
        delay(150);
      }

      delay(500);
    }
};

#endif
