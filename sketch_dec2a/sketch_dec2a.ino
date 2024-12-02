const int xPin = A0;
const int yPin = A1;
const int zPin = A2;

// Calibration offsets (adjust based on your sensor's behavior)
const int xOffset = 0;
const int yOffset = 0;
const int zOffset = 0;

// Sensitivity in mV/g (adjust based on your accelerometer's datasheet)
const float sensitivity = 330.0;

// Reference voltage of Arduino ADC
const float vRef = 3.3;
const int adcResolution = 1023;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read raw ADC values
  int xRaw = analogRead(xPin);
  int yRaw = analogRead(yPin);
  int zRaw = analogRead(zPin);

  // Convert raw values to voltages
  float xVoltage = (xRaw * vRef) / adcResolution;
  float yVoltage = (yRaw * vRef) / adcResolution;
  float zVoltage = (zRaw * vRef) / adcResolution;

  // Calculate acceleration in g's
  float xG = (xVoltage - (vRef / 2)) / (sensitivity / 1000);
  float yG = (yVoltage - (vRef / 2)) / (sensitivity / 1000);
  float zG = (zVoltage - (vRef / 2)) / (sensitivity / 1000);

  // Calculate roll and pitch in degrees
  float roll = atan2(yG, zG) * 180.0 / PI;
  float pitch = atan2(-xG, sqrt(yG * yG + zG * zG)) * 180.0 / PI;

  // Transmit data over serial
  Serial.print(roll);
  Serial.print(",");
  Serial.println(pitch);

  delay(50); // Reduce delay for faster updates
}


