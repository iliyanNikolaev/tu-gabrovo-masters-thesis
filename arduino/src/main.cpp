#include <DHT.h>

#define DHT_PIN 2 

DHT dht(DHT_PIN, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();
}


void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print(temperature);
  Serial.print("°C, ");
  Serial.print(humidity);
  Serial.println("%");

  delay(1000);
}
