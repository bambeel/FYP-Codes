/*
Pinouts:
Vcc = 5V Arduino
Gnd = GND Arduino
SCL = SCL Arduino
SDA = SDA Arduino
Vin+ = Vin Power Source
Vin- = Vin Load

Install Adafruit_INA219 library first

To use a slightly lower 32V, 1A range (higher precision on amps):
ina219.setCalibration_32V_1A();
Or to use a lower 16V, 400mA range, call:
ina219.setCalibration_16V_400mA();
*/

#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 sensorboard;

float shuntvoltage = 0.0;
float busvoltage = 0.0;
float current = 0.0;
float loadvoltage = 0.0;
float power = 0.0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }
  //initialize the INA219
  if (!sensorboard.begin()) {
    Serial.println("No Board Available");
    while (1) {
      delay(10);
    }
  }
  Serial.println("Measuring Voltage, Current & Power");
}

void loop() {
  shuntvoltage = sensorboard.getShuntVoltage_mV();
  busvoltage = sensorboard.getBusVoltage_V();
  current = sensorboard.getCurrent_mA();
  power = sensorboard.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  Serial.println("Bus Voltage:   "); Serial.print(busvoltage); Serial.print(" V");
  Serial.println("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.print(" mV");
  Serial.println("Load Voltage:  "); Serial.print(loadvoltage); Serial.print(" V");
  Serial.println("Current:       "); Serial.print(current); Serial.print(" mA");
  Serial.println("Power:         "); Serial.print(power); Serial.print(" mW");
}
