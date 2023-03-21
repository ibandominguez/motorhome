#ifndef RGBLed_h
#define RGBLed_h

class RGBLed {
private:
  int redPin;
  int greenPin;
  int bluePin;

public:
  RGBLed(int configRedPin, int configGreenPin, int configBluePin) {
    redPin = configRedPin;
    greenPin = configGreenPin;
    bluePin = configBluePin;
  }

  void begin() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
  }

  void write(int red, int green, int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
  }

  void clear() { write(0, 0, 0); }
};

#endif
