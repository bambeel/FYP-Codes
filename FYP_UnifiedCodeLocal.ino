#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2591.h>
#include <Adafruit_BME280.h>
#include <Adafruit_INA219.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_TSL2591 tsl2591 = Adafruit_TSL2591(2591);
Adafruit_BME280 bme280;
Adafruit_INA219 ina219;

float shuntvoltage = 0.0;
float busvoltage = 0.0;
float current = 0.0;
float loadvoltage = 0.0;
float power = 0.0;

void setup() {
  Serial.begin(9600);
  if (!tsl2591.begin()) {
    Serial.println("TSL2591 Unavailable");
  }
  if (!bme280.begin(0x76)) {
    Serial.println("BME280 Unavailable");
  }
  if (!ina219.begin()) {
    Serial.println("INA219 Unavailable");
  }

  tsl2591.setGain(TSL2591_GAIN_MED);
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_300MS);
}

void loop() {
  tsl2591_block();
  bme280_block();
  ina219_block();
  delay(500);
}

void tsl2591_block() {
  uint32_t tsl2591_data = tsl2591.getFullLuminosity();
  uint16_t ir;
  uint16_t ir_visible;

  ir = tsl2591_data >> 16;
  ir_visible = tsl2591_data & 0xFFFF;

  float lux = tsl2591.calculateLux(ir_visible, ir);
  Serial.print("Lux:");
  Serial.print(lux);
  Serial.println("");
}

void bme280_block() {
  Serial.print("Temperature = ");
  Serial.print(bme280.readTemperature());
  Serial.println("*C");

  Serial.print("Pressure = ");
  Serial.print(bme280.readPressure() / 100.0F);
  Serial.println("hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme280.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("m");

  Serial.print("Humidity = ");
  Serial.print(bme280.readHumidity());
  Serial.println("%");

  Serial.println();
}

void ina219_block() {
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();
  power = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  Serial.println(" ");
  Serial.print("Bus Voltage:   ");
  Serial.print(busvoltage);
  Serial.println(" V");

  Serial.print("Shunt Voltage: ");
  Serial.print(shuntvoltage);
  Serial.println(" mV");

  Serial.print("Load Voltage:  ");
  Serial.print(loadvoltage);
  Serial.println(" V");

  Serial.print("Current:       ");
  Serial.print(current);
  Serial.println(" mA");

  Serial.print("Power:         ");
  Serial.print(power);
  Serial.print(" mW");
  Serial.println("");
}
