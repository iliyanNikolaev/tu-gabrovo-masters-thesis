#include <DHT.h>
#include "MQ135.h"
#include <LiquidCrystal.h>

#define DHT_PIN 2

MQ135 gasSensor = MQ135(A1);
DHT dht(DHT_PIN, DHT22);
LiquidCrystal lcd(7, 8, 10, 11, 12, 13);
// LiquidCrystal(rs, enable, d4, d5, d6, d7)

int KY037_DIGITAL_PIN = 6;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  dht.begin();
  lcd.clear();
  lcd.print("Hello, A");
  lcd.setCursor(0, 1);
  lcd.print("rduino!");
}


void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float ppm = gasSensor.getCorrectedPPM(temperature, humidity);
  
  int dNoiseLevel = digitalRead(KY037_DIGITAL_PIN); 
  // 0 || 1

  Serial.println("Temperature: " + String(temperature) + "°C, Humidity: " + String(humidity) + "%, CO PPM: " + String(ppm));

  delay(300);
}