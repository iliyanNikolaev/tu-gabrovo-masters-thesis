#include <DHT.h>
#include "MQ135.h"
#include <LiquidCrystal.h>

#define DHT_PIN 2

MQ135 gasSensor = MQ135(A1);
DHT dht(DHT_PIN, DHT22);
LiquidCrystal lcd(7, 8, 10, 11, 12, 13);
// LiquidCrystal(rs, enable, d4, d5, d6, d7)

int KY037_DIGITAL_PIN = 6;
int KY037_ANALOG_PIN = A0;
int LED_PIN_1 = 3;
int resistor = 220;

void setup() {
  dht.begin();

  lcd.begin(16, 2);

  pinMode(KY037_DIGITAL_PIN, INPUT);
  pinMode(KY037_ANALOG_PIN, INPUT);

  pinMode(LED_PIN_1, OUTPUT);

  Serial.begin(9600);
}

char* KY037AnalogTodBParserWeb(int value) {
  if (value <= 327) {
    return "< 32.00 dB";
  } else if (value >= 328 && value <= 351) {
    return "32.01 - 35.00 dB";
  } else if (value >= 352 && value <= 440) {
    return "35.01 - 44.00 dB";
  } else if (value >= 441 && value <= 483) {
    return "44.01 - 49.00 dB";
  } else if (value >= 484 && value <= 544) {
    return "49.01 - 53.00 dB";
  } else if (value >= 545 && value <= 550) {
    return "53.01 - 56.00 dB";
  } else if (value >= 551 && value <= 611) {
    return "56.01 - 61.00 dB";
  } else if (value >= 612 && value <= 662) {
    return "61.01 - 65.00 dB";
  } else if (value >= 663 && value <= 764) {
    return "65.01 - 71.00 dB";
  } else if (value >= 765 && value <= 770) {
    return "71.01 - 78.00 dB";
  } else {
    return "> 72.00 dB";
  }
}

char* KY037AnalogTodBParserDisplay(int value) {
  if (value <= 327) {
    return "<32";
  } else if (value >= 328 && value <= 351) {
    return "32.1-35";
  } else if (value >= 352 && value <= 440) {
    return "35.1-44";
  } else if (value >= 441 && value <= 483) {
    return "44.1-49";
  } else if (value >= 484 && value <= 544) {
    return "49.1-53";
  } else if (value >= 545 && value <= 550) {
    return "53.1-56";
  } else if (value >= 551 && value <= 611) {
    return "56.1-61";
  } else if (value >= 612 && value <= 662) {
    return "61.1-65";
  } else if (value >= 663 && value <= 764) {
    return "65.1-71";
  } else if (value >= 765 && value <= 770) {
    return "71.1-78";
  } else {
    return ">72";
  }
}

int calculateBrightness(int noiseLevel, int maxResistorValue) {
  return map(noiseLevel, 0, 1, 0, maxResistorValue);
}

int counter = 0;

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float ppm = gasSensor.getCorrectedPPM(temperature, humidity);

  int dNoiseLevel = digitalRead(KY037_DIGITAL_PIN);  // 0 || 1
  int aNoiseLevel = analogRead(KY037_ANALOG_PIN);    // 0 - 1023
  char* dBNoiseLevelWeb = KY037AnalogTodBParserWeb(aNoiseLevel);
  char* dBNoiseLevelDisplay = KY037AnalogTodBParserDisplay(aNoiseLevel);

  int ledBrightness = calculateBrightness(dNoiseLevel, resistor);
  analogWrite(LED_PIN_1, ledBrightness);

  if (dNoiseLevel == 1) {
    digitalWrite(LED_PIN_1, HIGH);
  } else {
    digitalWrite(LED_PIN_1, LOW);
  }

  lcd.clear();
  if (counter < 75) {
    lcd.print("Temp: ");
    lcd.setCursor(0, 1);
    lcd.print(String(temperature)+" C");
  } else if (counter < 150) {
    lcd.print("Humid: ");
    lcd.setCursor(0, 1);
    lcd.print(String(humidity)+" %");
  } else if (counter < 300) {
    lcd.print("Co2");
    lcd.setCursor(0, 1);
    lcd.print(String(ppm)+"ppm");
  } else if (counter < 450) {
    lcd.print("Noise dB");
    lcd.setCursor(0, 1);
    lcd.print(dBNoiseLevelDisplay);
  } else if (counter == 451) {
    counter = 0;
    lcd.print("Temp: ");
    lcd.setCursor(0, 1);
    lcd.print(String(temperature)+" C");
  }

  Serial.println(String(temperature) + " °C, " + String(humidity) + " %, " + String(ppm) + " ppm, " + String(dBNoiseLevelWeb) + ", " + String(aNoiseLevel));

  counter++;

  delay(2);
}
