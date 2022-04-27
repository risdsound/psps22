// this is starter code for MIDI analog and digital inputs + i2c sensors for serial communication VL53LX1 and VCNL4040
// choose USB type Serial + MIDI in Teensyduino

#include "Adafruit_VL53L1X.h"
#include <Adafruit_VCNL4040.h>
Adafruit_VCNL4040 vcnl4040 = Adafruit_VCNL4040();
#define IRQ_PIN 2
#define XSHUT_PIN 3
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

// this section sets the analog pins, change where indicated

int const numPins = 3; // change the numer to how many analog pins you will use
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {
  0, 1, 2// list the numbers of each pin you will use seperated by a comma
};


// set digital pins

int const numDigPinsCC = 4; // change the number to how many digital pins you will use
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
  0 // list the numbers of each pin you will use seperated by a comma
};

int digInputcc[numDigPinsCC];

// the MIDI channel number to send messages
const int channel = 2; // set to channel 2 so that it can be used with other MIDI controllers




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


  Serial.println("Adafruit VCNL4040 Config demo");

  if (!vcnl4040.begin()) {
    Serial.println("Couldn't find VCNL4040 chip");
    while (1);
  }
  Serial.println("Found VCNL4040 chip");

  // set pin modes for digital pins for MIDI

  pinMode(0, INPUT_PULLUP);
  //  pinMode(1, INPUT_PULLUP);
  //  pinMode(2, INPUT_PULLUP);
  //  pinMode(3, INPUT_PULLUP);
  //  pinMode(4, INPUT_PULLUP);
  //  pinMode(5, INPUT_PULLUP);
  //  pinMode(6, INPUT_PULLUP);
  //  pinMode(7, INPUT_PULLUP);
  //  pinMode(8, INPUT_PULLUP);
  //  pinMode(9, INPUT_PULLUP);
  //  pinMode(10, INPUT_PULLUP);
  //  pinMode(11, INPUT_PULLUP);
  //  pinMode(12, INPUT_PULLUP);
  //  pinMode(13, INPUT_PULLUP);
}

void loop() {

  // MIDI digital pins input sending CC messages beginning at ctlin 51 for Pd

  for (int i = 0; i < numDigPinsCC; i++) {
    if (digitalRead(digitalpincc[i]) == 1 && currentDigcc[i] == 0) {
      usbMIDI.sendControlChange(i + 51, 0, channel);
      currentDigcc[i] = 1;
    }
    if (digitalRead(digitalpincc[i]) == 0  && currentDigcc[i] == 1) {
      usbMIDI.sendControlChange(i + 51, 127, channel);
      currentDigcc[i] = 0;
    }
  }

  // MIDI analog pins input sending CC messages beginning at ctlin 1 for Pd

  for (int i = 0; i < numPins; i++) {

    newVal[i] = analogRead(analogPins[i]);

    if (abs(newVal[i] - currentVal[i]) > 3) {
      usbMIDI.sendControlChange(i + 1, newVal[i] >> 3, channel);
      currentVal[i] = newVal[i];
    }

  }
  // MIDI Controllers can discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash

  while (usbMIDI.read()) {
    // ignore incoming messages
  }

  // distance sensor i2c
  int16_t dist;
  if (vl53.dataReady()) {
    dist = vl53.distance();
    Serial.print("distance: "); // in mm
    Serial.print(dist);
    Serial.print(" ");
    Serial.println(" ");
    vl53.clearInterrupt();
  }

  // proximity sensor i2c
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
