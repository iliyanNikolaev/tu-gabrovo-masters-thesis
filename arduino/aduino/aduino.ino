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

void setup() {
  dht.begin();

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Hello, A");
  lcd.setCursor(0, 1);
  lcd.print("rduino!");

  pinMode(KY037_DIGITAL_PIN, INPUT);
  pinMode(KY037_ANALOG_PIN, INPUT);
  
  Serial.begin(9600);
}

char* KY037AnalogTodBParser(int value) {
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

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float ppm = gasSensor.getCorrectedPPM(temperature, humidity);

  int dNoiseLevel = digitalRead(KY037_DIGITAL_PIN);  // 0 || 1
  int aNoiseLevel = analogRead(KY037_ANALOG_PIN); // 0 - 1023
  char* dBNoiseLevel = KY037AnalogTodBParser(aNoiseLevel);

  Serial.println("Temperature: " + String(temperature) + "°C, Humidity: " + String(humidity) + "%, CO PPM: " + String(ppm) + ", Noise(GM1352): " + String(dBNoiseLevel) + ", KY037 Analog Value: " + String(aNoiseLevel));
  // Serial.println(aNoiseLevel);

  delay(50);
}
