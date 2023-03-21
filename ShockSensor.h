#ifndef ShockSensor_h
#define ShockSensor_h

class ShockSensor {
  private:
    int pin;

  public:
    ShockSensor(int configPin) {
      pin = configPin;
    }

    void begin() {
      pinMode(pin, INPUT);
    }
    
    int isOnShock() {
      return digitalRead(pin) == HIGH;
    }   
};

#endif