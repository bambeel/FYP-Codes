/*
install adafruit tsl2591 library\

Pinout:
Vin: 5V pin
GND: Ground Arduino
INT: Interrupt Pin
SDA: Serial Data Pin 
SCL: Serial Clock Pin
*/

#include <Adafruit_TSL2591.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_TSL2591 sensorboard = Adafruit_TSL2591(2591);

void setup() {
  Serial.begin(9600);
  if (sensorboard.begin()) {
    Serial.println("Board Found");
  } else {
    Serial.println("Board Not Found");
    while (1) {
      delay(10);
    }
  }
  sensorboard.setGain(TSL2591_GAIN_MED);
  sensorboard.setTiming(TSL2591_INTEGRATIONTIME_300MS);
}

void loop() {
  uint32_t tsl2591_data = sensorboard.getFullLuminosity();
  uint16_t ir;
  uint16_t ir_visible;

  ir = tsl2591_data >> 16;
  ir_visible = tsl2591_data & 0xFFFF;

  float lux = sensorboard.calculateLux(ir_visible, ir);
  Serial.println("Lux:  ");
  Serial.print(lux);

  delay (500);
}
