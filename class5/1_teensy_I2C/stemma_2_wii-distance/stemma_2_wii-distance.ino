#include <WiiChuck.h>
Accessory nunchuck;

#include "Adafruit_VL53L1X.h"
#define IRQ_PIN 2
#define XSHUT_PIN 3

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

void setup() {
  Serial.begin(9600);
  nunchuck.begin();
  if (nunchuck.type == Unknown) {
    nunchuck.type = NUNCHUCK;
  }
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
  
  nunchuck.readData();    // Read inputs and update maps

  int wiix = nunchuck.getAccelX();
  Serial.print("nx: "); 
  Serial.print(wiix);
  Serial.print(" ");
  Serial.println(" ");

  int wiiy = nunchuck.getAccelY();
  Serial.print("ny: "); 
  Serial.print(wiiy);
  Serial.print(" ");
  Serial.println(" ");

  int wiiz = nunchuck.getAccelZ();
  Serial.print("nz: "); 
  Serial.print(wiiz);
  Serial.print(" ");
  Serial.println(" ");

  int wiijx = nunchuck.getJoyX();
  Serial.print("jx: "); 
  Serial.print(wiijx);
  Serial.print(" ");
  Serial.println(" ");

  int wiijy = nunchuck.getJoyY();
  Serial.print("jy: "); 
  Serial.print(wiijy);
  Serial.print(" ");
  Serial.println(" ");
  
  int wiibz = nunchuck.getButtonZ();
  Serial.print("bz: "); 
  Serial.print(wiibz);
  Serial.print(" ");
  Serial.println(" ");

  int wiibc = nunchuck.getButtonC();
  Serial.print("bc: "); 
  Serial.print(wiibc);
  Serial.print(" ");
  Serial.println(" ");
  
  delay(20);
}
