#include <DHT.h>

#define DHT_PIN 2
int KY037_DIGITAL_PIN = 6;
int MQ135_PIN = A1;

DHT dht(DHT_PIN, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();
}


void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int dNoiseLevel = digitalRead(KY037_DIGITAL_PIN);
  int gasValue = analogRead(MQ135_PIN);
  Serial.print(temperature);
  Serial.print("°C, ");
  Serial.print(humidity);
  Serial.print(", Gas Value: ");
  Serial.println(gasValue);

  delay(50);
}