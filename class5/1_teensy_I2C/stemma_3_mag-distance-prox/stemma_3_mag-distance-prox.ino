#include <Tlv493d.h>
// Tlv493d Opject
Tlv493d Tlv493dMagnetic3DSensor = Tlv493d();

#include "Adafruit_VL53L1X.h"

#define IRQ_PIN 2
#define XSHUT_PIN 3

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);


#include <Adafruit_VCNL4040.h>

Adafruit_VCNL4040 vcnl4040 = Adafruit_VCNL4040();

void setup() {
  Serial.begin(9600);



  while (!Serial) delay(10);

  Serial.println(F("Adafruit VL53L1X sensor demo"));

  Wire.begin();
  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("VL53L1X sensor OK!"));

  Serial.print(F("Sensor ID: 0x"));
  Serial.println(vl53.sensorID(), HEX);

  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(vl53.getTimingBudget());

  /*
    vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
    vl.VL53L1X_SetInterruptPolarity(0);
  */

  while (!Serial);
  Tlv493dMagnetic3DSensor.begin();
  Tlv493dMagnetic3DSensor.setAccessMode(Tlv493dMagnetic3DSensor.MASTERCONTROLLEDMODE);
  Tlv493dMagnetic3DSensor.disableTemp();


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
  int16_t dist;
  if (vl53.dataReady()) {
    dist = vl53.distance();
    Serial.print("distance: "); // in mm
    Serial.print(dist);
    Serial.print(" ");
    Serial.println(" ");
    vl53.clearInterrupt();
  }

  delay(Tlv493dMagnetic3DSensor.getMeasurementDelay());
  Tlv493dMagnetic3DSensor.updateData();

  float magX = Tlv493dMagnetic3DSensor.getX();
  Serial.print("mx: ");
  Serial.print(magX);
  Serial.print(" ");
  Serial.println(" ");

  float magY = Tlv493dMagnetic3DSensor.getY();
  Serial.print("my: ");
  Serial.print(magY);
  Serial.print(" ");
  Serial.println(" ");

  float magZ = Tlv493dMagnetic3DSensor.getZ();
  Serial.print("mz: ");
  Serial.print(magZ);
  Serial.print(" ");
  Serial.println(" ");

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
