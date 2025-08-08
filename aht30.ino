#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(0x38, 4);
  while (Wire.available() < 4);
  uint16_t h = Wire.read() << 8 | Wire.read();
  uint16_t t = Wire.read() << 8 | Wire.read();

  Serial.print("Humidity: ");
  Serial.print(h / 100.0);
  Serial.print("%  Temp: ");
  Serial.print(t / 100.0);
  Serial.println("°C");

  delay(2000);
}
