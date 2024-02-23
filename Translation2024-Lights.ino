#include <Wire.h>
#include <PolledTimeout.h>

const int16_t I2C_LIGHT_ADDR = 0x2C;
const int16_t I2C_TOUCH_ADDR = 0x8C;
#define SDA_PIN 4
#define SCL_PIN 5

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN, I2C_LIGHT_ADDR);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(74880);

}

void loop() {
  using periodic = esp8266::polledTimeout::periodicMs;
  static periodic nextPing(100);

  digitalWrite(LED_BUILTIN, HIGH);

  if (nextPing) {
    Wire.requestFrom(I2C_TOUCH_ADDR, 1);  // request a bytes from 
    Serial.print("Requested: ");

    while (Wire.available()) {  // slave may send less than requested
      char c = Wire.read();     // receive a byte as character
      Serial.print(c);          // print the character
      digitalWrite(LED_BUILTIN, LOW);  // Flicker the light
    }
    Serial.println();
  }
}

