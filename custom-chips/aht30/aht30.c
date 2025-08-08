#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float humidity;     // ความชื้น (%)
  float temperature;  // อุณหภูมิ (°C)
} chip_state_t;

// เริ่มต้นชิป
void chip_init(void *user_data) {
  chip_state_t *state = (chip_state_t*)user_data;
  state->humidity = 50.0;    // ค่าเริ่มต้น
  state->temperature = 25.0; // ค่าเริ่มต้น
}

// อัพเดตค่าจาก slider ใน chip.json
void chip_set_control(void *user_data, uint8_t control_id, float value) {
  chip_state_t *state = (chip_state_t*)user_data;
  switch (control_id) {
    case 0: state->humidity = value; break;    // humidityPercent
    case 1: state->temperature = value; break; // temperatureC
  }
}

// เมื่อถูกอ่านจาก I2C
int chip_i2c_read(void *user_data, uint8_t reg, uint8_t *buf, uint8_t len) {
  chip_state_t *state = (chip_state_t*)user_data;

  // แปลงความชื้นและอุณหภูมิเป็นหน่วยร้อย (เช่น 55.34% -> 5534)
  uint16_t hum = (uint16_t)(state->humidity * 100);
  uint16_t temp = (uint16_t)(state->temperature * 100);

  if (len >= 4) {
    buf[0] = hum >> 8;
    buf[1] = hum & 0xFF;
    buf[2] = temp >> 8;
    buf[3] = temp & 0xFF;
    return 4; // จำนวนไบต์ที่ส่งกลับ
  }
  return 0;
}

// บอกขนาดหน่วยความจำที่จะใช้เก็บ state
uint32_t chip_get_state_size() {
  return sizeof(chip_state_t);
}
