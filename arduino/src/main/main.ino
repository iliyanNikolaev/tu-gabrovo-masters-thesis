#include <DHT.h>

#define DHT_PIN 2
const int KY037_PIN = A0;
const int MQ135_PIN = A1;

DHT dht(DHT_PIN, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();
}


void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int noiseLevel = analogRead(KY037_PIN);
  int gasValue = analogRead(MQ135_PIN);
  Serial.print(temperature);
  Serial.print("°C, ");
  Serial.print(humidity);
  Serial.print("%, Noise level: ");
  Serial.print(noiseLevel);
  Serial.print(", Gas Value: ");
  Serial.println(gasValue);

  delay(500);
}