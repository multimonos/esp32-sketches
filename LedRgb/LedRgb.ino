#include <cstdint>
#include <esp_log.h>
//
// Pin mappings for esp32 are at https://github.com/espressif/arduino-esp32/blob/14095487f6628807ae92b22ff268f12ea51559ad/variants/esp32/pins_arduino.h
//

const uint8_t R = A4;
const uint8_t B = A5;
const uint8_t G = A18;

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

Color colors[5] = {
  {255,211,25},
  {255,144,31},
  {255,43,92},
  {255,61,244},
  {154,52,235}
};

void setup() {
  ledcAttach(R, 12000, 8);
  ledcAttach(G, 12000, 8);
  ledcAttach(B, 12000, 8);
  Serial.begin(115200);
}

void loop() {

  size_t len = sizeof(colors) / sizeof(colors[0]);

  for (int i=0; i < len; i++) {
    ledcWrite(R, colors[i].r);
    ledcWrite(G, colors[i].g);
    ledcWrite(B, colors[i].b);
    Serial.printf("\n%d : (r,g,b) = (%d, %d, %d)", i, colors[i].r, colors[i].g, colors[i].b);
    delay(500);
  }
}
