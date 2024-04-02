/*
  TCA9548A Mapping;
  Port 1 = BME280
  Port 2 = INA219
  Port 4 = LCD Display
  Port 7 = TSL2591

  I2C Addresses
  BME280: 0x76
  INA219: 0x40
  LCD Display: 0x27
  TSL2591: 0x29
  I2C MUX: 0x70

  Master Lora Node
  GND : Combine and connect to GND
  3V3 : 3.3V
  RST: 9
  DIO0: 8
  NSS: 10
  MOSI: 51
  MISO: 50
  SCK: 52
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2591.h>
#include <Adafruit_BME280.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal_I2C.h>
#include <LoRa.h>

#define SEALEVELPRESSURE_HPA (1013.25)

LiquidCrystal_I2C lcd(0x27, 20, 4);  // initialize lcd display

// initialize sensors
Adafruit_TSL2591 tsl2591 = Adafruit_TSL2591(2591);
Adafruit_BME280 bme280;
Adafruit_INA219 ina219;

//initialize sensors state
int bmestate;
int tslstate;
int inastate;

//initialize sensor variables
float lux = 0.0;
float irradiance = 0.0;

float alt = 0.0;
float temp = 0.0;
float pressure = 0.0;
float humidity = 0.0;

float shuntvoltage = 0.0;
float busvoltage = 0.0;
float current = 0.0;
float loadvoltage = 0.0;
float power = 0.0;

// variables for lora
byte msgcount;
int master = "master";
String slave = "node1";
String msg = "";

void TCA9548A(uint8_t bus) {  // block for tca9548a
  Wire.beginTransmission(0x70);
  Wire.write(1 << bus);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  Wire.begin();

  LoRa.setPins(10, 9, 8);  // NSS, Reset, DIO0
  while (!Serial)
    ;
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa Failed");
    while (1)
      ;
  } else {
    Serial.println("LoRa Initialization Successful");
  }

  //initialization of BME280
  TCA9548A(1);
  if (!bme280.begin(0x76)) {
    Serial.println("BME280 Unavailable");
    lcd.setCursor(0, 1);
    lcd.print("BME280 Unavailable");
  } else {
    bmestate = 1;
  }

  //initialization of INA219
  TCA9548A(2);
  if (!ina219.begin()) {
    Serial.println("INA219 Unavailable");
    lcd.setCursor(0, 2);
    lcd.print("INA219 Unavailable");
  } else {
    inastate = 1;
  }

  //initiatlization of TSL2591
  TCA9548A(7);
  if (!tsl2591.begin()) {
    Serial.println("TSL2591 Unavailable");
    lcd.setCursor(0, 0);
    lcd.print("TSL2591 Unavailable");
  } else {
    tslstate = 1;
  }
  // LCD display systems check
  lcdinit_block(4);
  tsl2591.setGain(TSL2591_GAIN_LOW);
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_100MS);
  ina219.setCalibration_32V_2A();

  /*
  --TSL2591 Gain Values--
  tsl2591.setGain(TSL2591_GAIN_LOW);  // 1x gain (bright light)
  tsl2591.setGain(TSL2591_GAIN_MED);  // 25x gain
  tsl2591.setGain(TSL2591_GAIN_HIGH); // 428x gain
  tsl2591.setGain(TSL2591_GAIN_MAX);  // 9876x gain

  --TSL2591 Integration Times
  Changing the integration time gives you a longer time over which to sense light
  longer timelines are slower, but are good in very low light situtations!
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_200MS);
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_400MS);
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_500MS);
  tsl2591.setTiming(TSL2591_INTEGRATIONTIME_600MS);

  --INA219 Set Calibration--
  ina219.setCalibration_32V_2A();
  ina219.setCalibration_32V_1A();
  ina219.setCalibration_16V_400mA();
  */
}

void loop() {
  tsl2591_block(7);
  ina219_block(2);
  bme280_block(1);
  lcd_block(4);
/*
  //debug tsl2591
  Serial.print("Lux: ");
  Serial.println(lux);
  Serial.print("Irradiance: ");
  Serial.println(irradiance);
  //debug ina219
  Serial.print("Bus Voltage: ");
  Serial.println(busvoltage);
  Serial.print("Current: ");
  Serial.println(current);
  Serial.print("Power: ");
  Serial.println(power);
  // debug bme280
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Pressure = ");
  Serial.println(pressure);
  Serial.print("Approx. Altitude = ");
  Serial.println(alt);
  Serial.print("Humidity = ");
  Serial.println(humidity);
*/
  // packet construct for lora send
  msg = msg + master + ',' + slave + ',' + lux + ',' + irradiance + ',' + busvoltage + ',' + current + ',' + power + ',' + temp + ',' + pressure;
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
  Serial.print("Message Structure: ");
  Serial.println(msg);
  msg = "";
  Serial.println("");
}

void lcdinit_block(int bus) {
  TCA9548A(bus);
  if ((tslstate == 1) && (bmestate == 1) && (inastate == 1)) {
    lcd.setCursor(1, 0);
    lcd.print("WELCOME TO UN-VEIL");
    lcd.setCursor(1, 1);
    lcd.print("------------------");
    lcd.setCursor(1, 2);
    lcd.print("ALL SENSORS ONLINE");
    lcd.setCursor(1, 3);
    lcd.print("SYSTEM INITIALIZED");
    delay(2000);
    lcd.clear();

    // arrangement of functions
    lcd.setCursor(0, 0);
    lcd.print("BV:");
    lcd.setCursor(8, 0);
    lcd.print("LV:");
    lcd.setCursor(0, 1);
    lcd.print("AMP:");
    lcd.setCursor(9, 1);
    lcd.print("WATT:");
    lcd.setCursor(0, 2);
    lcd.print("TEMP:");
    lcd.setCursor(10, 2);
    lcd.print("hPA:");
    lcd.setCursor(0, 3);
    lcd.print("LUX:");
    lcd.setCursor(10, 3);
    lcd.print("IRR:");
  }
}

void tsl2591_block(int bus) {
  //start block for TSL2591
  TCA9548A(bus);
  uint32_t tsl2591_data = tsl2591.getFullLuminosity();
  uint16_t ir;
  uint16_t ir_visible;
  ir = tsl2591_data >> 16;
  ir_visible = tsl2591_data & 0xFFFF;
  lux = tsl2591.calculateLux(ir_visible, ir);
  irradiance = lux * 0.0079;
  // end block for TSL2591
  return lux, irradiance;
}

void ina219_block(int bus) {
  // start block for INA219
  TCA9548A(bus);
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();
  power = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  // end block for INA219
  return busvoltage, shuntvoltage, loadvoltage, current, power;
}

void bme280_block(int bus) {
  // start block for BME280
  TCA9548A(bus);
  alt = bme280.readAltitude(SEALEVELPRESSURE_HPA);
  temp = bme280.readTemperature();
  pressure = bme280.readPressure() / 100.0F;
  humidity = bme280.readHumidity();
  // end block for TSL2591
  return temp, pressure;
}

void lcd_block(int bus) {
  TCA9548A(bus);
  // for TSL2591
  lcd.setCursor(4, 3);
  lcd.print(lux);
  lcd.setCursor(14, 3);
  lcd.print(irradiance);
  // for BME280
  lcd.setCursor(5, 2);
  lcd.print(temp, 1);
  lcd.setCursor(14, 2);
  lcd.print(pressure, 1);
  // for INA219
  lcd.setCursor(3, 0);
  lcd.print(busvoltage);
  lcd.setCursor(11, 0);
  lcd.print(loadvoltage);
  lcd.setCursor(4, 1);
  lcd.print(current);
  lcd.setCursor(14, 1);
  lcd.print(power);
}
