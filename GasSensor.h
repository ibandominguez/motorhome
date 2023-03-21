#ifndef GasSensor_h
#define GasSensor_h

class GasSensor
{
private:
  int pin;

public:
  GasSensor(int configPin)
  {
    pin = configPin;
  }

  void begin()
  {
    pinMode(pin, INPUT);
  }

  bool hasGas()
  {
    return digitalRead(pin) == LOW;
  }

  void onAlert(void (*callback)(void))
  {
    if (hasGas())
    {
      callback();
    }
  }
};

#endif
