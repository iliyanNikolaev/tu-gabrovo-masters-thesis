#include <DHT.h>
#include "MQ135.h"

#define DHT_PIN 2

MQ135 gasSensor = MQ135(A1);
DHT dht(DHT_PIN, DHT22);

int KY037_DIGITAL_PIN = 6;

void setup() {
  Serial.begin(9600);
  dht.begin();
}


void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float ppm = gasSensor.getCorrectedPPM(temperature, humidity);
  
  int dNoiseLevel = digitalRead(KY037_DIGITAL_PIN); // 0 || 1

  Serial.println("Temperature: " + String(temperature) + "°C, Humidity: " + String(humidity) + "%, CO PPM: " + String(ppm));

  delay(300);
}