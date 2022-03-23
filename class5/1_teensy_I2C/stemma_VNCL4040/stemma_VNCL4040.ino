#include <Adafruit_VCNL4040.h>

Adafruit_VCNL4040 vcnl4040 = Adafruit_VCNL4040();

void setup() {
  Serial.begin(9600);
  // Wait until serial port is opened
  while (!Serial) {
    delay(1);
  }

  Serial.println("Adafruit VCNL4040 Config demo");

  if (!vcnl4040.begin()) {
    Serial.println("Couldn't find VCNL4040 chip");
    while (1);
  }
  Serial.println("Found VCNL4040 chip");
}

void loop() {

  float proxVal = vcnl4040.getProximity();
  Serial.print("proximity: ");
  Serial.print(proxVal);
  Serial.print(" ");
  Serial.println(" ");

  float ambVal = vcnl4040.getLux();
  Serial.print("ambient: "); // ambient light
  Serial.print(ambVal);
  Serial.print(" ");
  Serial.println(" ");

  float rawVal = vcnl4040.getWhiteLight();
  Serial.print("raw: "); // raw white light
  Serial.print(rawVal);
  Serial.print(" ");
  Serial.println("");

  delay(20);
}
