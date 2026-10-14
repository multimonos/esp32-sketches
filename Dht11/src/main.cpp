#include "DHT.h"
#include "HardwareSerial.h"
#include "esp32-hal.h"
#include <Arduino.h>
#include <cmath>
#include <cstdint>
#include <esp_log.h>

constexpr uint8_t DHT_GPIO = 32;

DHT dht(DHT_GPIO, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  // wait for dht to spinup
  delay(3000);

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  // check sensor reading
  if (isnan(humidity)) {
    Serial.println("! failed to read humidity");
    return;
  }
  if (isnan(temp)) {
    Serial.println("! failed to read temperature");
    return;
  }

  Serial.printf("{ \"temp\": %f, \"humidity\": %f }\n", temp, humidity);
}
