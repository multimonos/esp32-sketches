#include <esp_log.h>

void setup() {
  Serial.begin(115200); // esp32 requires esp_log.h
}

void loop() {
  Serial.printf("noop\n");
  delay(3000);
}
