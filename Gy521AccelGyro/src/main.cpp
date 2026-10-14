#include "HardwareSerial.h"
#include "esp32-hal.h"
#include <Arduino.h>
#include <Wire.h>
#include <cstdint>
#include <esp_log.h>

constexpr uint8_t MPU_ADDR = 0x68;
constexpr uint8_t WHOAMI_REG = 0x75;
constexpr uint8_t PWR_MGMT = 0x6B;
constexpr uint8_t ACCEL_XOUT_H = 0x3B;

void printWhoamiRegister(uint8_t mpuAddress, uint8_t whoamiRegister) {
  Wire.beginTransmission(mpuAddress);
  Wire.write(whoamiRegister);
  uint8_t err = Wire.endTransmission(false);

  if (err != 0) {
    Serial.printf("! WireError: %d\n", err);

  } else {
    Wire.requestFrom(mpuAddress, static_cast<uint8_t>(1));

    if (!Wire.available()) {
      Serial.println("! Wire not available.");
      return;
    }

    uint8_t chipId = Wire.read();
    Serial.printf("whoami_register: 0x%02X\n", chipId);

    if (chipId == 0x70) {
      Serial.println("model: 6500, dof: 6");
    }
    if (chipId == 0x68) {
      Serial.println("model: 6050, dof: 6");
    }
    if (chipId == 0x71) {
      Serial.println("model: 9250, dof: 9");
    }
    if (chipId == 0x73) {
      Serial.println("model: 9255, dof: 9");
    }
  }
}

void printDataset(uint8_t mpuAddress) {
  Wire.beginTransmission(mpuAddress);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);

  if (Wire.requestFrom(mpuAddress, static_cast<uint8_t>(6)) == 6) {
    int16_t ax = (Wire.read() << 8) | Wire.read();
    int16_t ay = (Wire.read() << 8) | Wire.read();
    int16_t az = (Wire.read() << 8) | Wire.read();

    float accelx = ax / 16384.0f;
    float accely = ay / 16384.0f;
    float accelz = az / 16384.0f;

    Serial.printf("{ \"accel\": { \"x\": %.2f, \"y\": %2.f, \"z\": %2.f } }\n",
                  accelx, accely, accelz);
  }
}

void setup() {
  Serial.begin(115200);

  delay(2000);

  Wire.begin(21, 22);
  Wire.setTimeOut(50);

  printWhoamiRegister(MPU_ADDR, WHOAMI_REG);
}

void loop() {
  printDataset(MPU_ADDR);
  delay(250);
}
