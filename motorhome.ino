#include "DHT.h"
#include "RGBLed.h"
#include "Song.h"
#include "InterrupButton.h"
#include "ShockSensor.h"
#include "LcdAnimation.h"
#include "ModeController.h"
#include "GasSensor.h"

#define LCD_RS A0
#define LCD_EN A1
#define LCD_D0 A2
#define LCD_D1 A3
#define LCD_D2 A4
#define LCD_D3 A5
#define BUTTON_PIN 2
#define BUZZER_PIN 3
#define GAS_SENSOR_PIN 4
#define DHT_PIN 5
#define LCD_ANALOG_V_PIN 6
#define SHOCK_SENSOR_PIN 7
#define RGB_RED_PIN 9
#define RGB_GREEN_PIN 10
#define RGB_BLUE_PIN 11
#define LCD_ANALOG_V_VAL 80

DHT dht(DHT_PIN, DHT11);
RGBLed rgbLed(RGB_RED_PIN, RGB_GREEN_PIN, RGB_GREEN_PIN);
Song song(BUZZER_PIN);
ShockSensor shockSensor(SHOCK_SENSOR_PIN);
LcdAnimation lcd(LCD_RS, LCD_EN, LCD_D0, LCD_D1, LCD_D2, LCD_D3);
ModeController modeController("Temperatura");
GasSensor gasSensor(GAS_SENSOR_PIN);
InterrupButton interrupButton(BUTTON_PIN);

void setup() {
  dht.begin();
  gasSensor.begin();
  shockSensor.begin();
  rgbLed.begin();
  lcd.begin(16, 2);

  interrupButton.begin([]() {
    String mode = modeController.getMode();
    if (mode == "Temperatura") return modeController.setMode("Bateria");
    if (mode == "Bateria") return modeController.setMode("Alarma");
    if (mode == "Alarma") return modeController.setMode("Sleep");
    return modeController.setMode("Temperatura");
  });

  lcd.setupPWMContrastPin(LCD_ANALOG_V_PIN, LCD_ANALOG_V_VAL);
  lcd.setupIcons();

  lcd.playFamilyAnimation();

  song.play([]() {
    lcd.toggleIntroAnimation();
    rgbLed.write(random(0, 255), random(0, 255), random(0, 255));
  });

  modeController.reset();
}

void loop() {
  // Check gasSensor
  gasSensor.onAlert([]() {
    lcd.clear();
    lcd.home();

    while (gasSensor.hasGas()) {
      lcd.write("-- ADVERTENCIA --");
      lcd.setCursor(0, 1);
      lcd.write("GAS DETECTADO   ");
      tone(BUZZER_PIN, 1000);
      delay(1000);      
    }
    
    noTone(BUZZER_PIN);
    modeController.reset();
  });

  // Mode change handler
  modeController.onChange([]() {
    rgbLed.clear(); 
    lcd.clear();
    lcd.renderHomeMotorhomeIcon();
    lcd.setCursor(4, 0);
    lcd.write(modeController.getMode().c_str());
  });

  // Temperature mode
  modeController.on("Temperatura", []() {
    float temperature = dht.readTemperature(false);
    float humidity = dht.readHumidity();
    
    // Check for error
    lcd.setCursor(4, 1);
    if (isnan(humidity) || isnan(temperature)) {
      lcd.write("Error sensor");
    } else {
      String output = String(String(temperature) + " " + String(humidity) + "%");
      lcd.write(output.c_str());
    }
  });

  // Battery mode
  modeController.on("Bateria", []() {
    lcd.setCursor(4, 1);
    lcd.write("...");
  });

  // Alarm mode
  modeController.on("Alarma", []() {
    lcd.setCursor(4, 1);
    lcd.write("...");
  });

  // Sleep mode
  modeController.on("Sleep", []() {
    lcd.setCursor(4, 1);
    lcd.write("...");
  });
}
