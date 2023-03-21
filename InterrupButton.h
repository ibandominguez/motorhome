#ifndef InterrupButton_h
#define InterrupButton_h

class InterrupButton {
  private:
    int pin;
    
  public:
    InterrupButton(int configPin) {
      pin = configPin;
    }

    void begin(void (*callback(void))) {
      pinMode(pin, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(pin), callback, RISING);
    }
};

#endif
