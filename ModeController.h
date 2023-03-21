#ifndef ModeController_h
#define ModeController_h

#define MIN_MODE_MILLIS 350

class ModeController {
  private:
    String mode = "Temperatura";
    bool modeChanged = false;
    unsigned long lastSetTimeStamp = millis();
  
  public:
    ModeController(String initialMode = "Temperatura") {
      mode = initialMode;
    }

    void setMode(String newMode) {
      unsigned long timestamp = millis();
      if (timestamp - lastSetTimeStamp < MIN_MODE_MILLIS) {
        return;
      }
      lastSetTimeStamp = timestamp;
      modeChanged = mode != newMode;
      mode = newMode;
    }

    String getMode() {
      return mode;
    }

    void reset() {
      setMode("Temperatura");
      modeChanged = true;
    }

    void on(String comparingMode, void (*callback)(void)) {
      if (mode == comparingMode) {
        callback();
      }
    }

    void onChange(void (*callback)(void)) {
      if (modeChanged) {
        callback();
        modeChanged = false;
      }
    }
};

#endif
