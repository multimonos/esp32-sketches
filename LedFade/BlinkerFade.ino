// NOTE: The analogWrite() is not available on esp32.

const uint8_t PIN = 33;

// int bright = 0;
// int fade = 5;

// void setup() {
//   ledcAttach(PIN, 12000, 8);
// }

// void loop() {
//   ledcWrite(PIN, bright);

//   // ramp from 0 -> 255
//   bright = (bright + fade) % 255;

//   delay(50);
// }


// ALTERNATE version taking advantage of uint8_t space.
uint8_t bright = 0;
uint8_t fade = 5;

void setup() {
  ledcAttach(PIN, 12000, 8);
}

void loop(){
  ledcWrite(PIN, bright);

  bright += fade; // will auto-wrap as 255 + n = 0 for uint8_t

  delay(50);
}