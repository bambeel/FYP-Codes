/*
S is signal output, so use analog input
G is ground
proportion mapping method, so read directly from the board
need to code using voltage divider method
*/
float read_voltage = 0.0;
float in_voltage = 0.0;

//declaring resistors based on module
float r1 = 30000.0;
float r2 = 7500.0;

//ref voltage
float ref_voltage = 5.0;

int read_value = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  read_value = analogRead(A0);
  read_voltage = (read_value * ref_voltage) / 1024.0;
  in_voltage = read_voltage * (r1 + r2) / r2;

  Serial.println("voltage read: ");
  Serial.print(in_voltage);
}
