#include <Adafruit_VCNL4040.h>

Adafruit_VCNL4040 vcnl4040 = Adafruit_VCNL4040();

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS331HH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS331HH_SCK 13
#define LIS331HH_MISO 12
#define LIS331HH_MOSI 11
// Used for hardware & software SPI
#define LIS331HH_CS 10

Adafruit_LIS331HH lis = Adafruit_LIS331HH();

// analog values array size, must be constant
const int num_of_analog_pins = 1; // total numer of analog pins
int analog_values[num_of_analog_pins];
int analog_pins[] = {
  0,// list each analog pin to use
};

// touch values array size, must be constant
const int num_of_touch_pins = 4; // total numer of analog pins
int touch_values[num_of_touch_pins];
int touch_pins[] = {
  1, 3, 4, 23 // list each touch pin to use
};


void setup() {

  // analogReadResolution(12); // Teensy is 12bit ADC, you can set to 12 but this will introduce some noise, also you can set lower like 7bit for MIDI range
  analogReadAveraging(32); // Teensy can do averaging of samples in hardware, set to 4, 8, 16, 32

  Serial.begin(9600);
  // Wait until serial port is opened
  while (!Serial) {
    delay(10);
  }

  Serial.println("LIS331HH test!");

  //if (!lis.begin_SPI(LIS331HH_CS)) {
//  if (!lis.begin_SPI(LIS331HH_CS, LIS331HH_SCK, LIS331HH_MISO, LIS331HH_MOSI)) {
  if (! lis.begin_I2C()) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS331HH found!");

 lis.setRange(LIS331HH_RANGE_6_G);   // 6, 12, or 24 G
  Serial.print("Range set to: ");
  switch (lis.getRange()) {
    case LIS331HH_RANGE_6_G: Serial.println("6 g"); break;
    case LIS331HH_RANGE_12_G: Serial.println("12 g"); break;
    case LIS331HH_RANGE_24_G: Serial.println("24 g"); break;
  }
  // lis.setDataRate(LIS331_DATARATE_50_HZ);
  Serial.print("Data rate set to: ");
  switch (lis.getDataRate()) {

    case LIS331_DATARATE_POWERDOWN: Serial.println("Powered Down"); break;
    case LIS331_DATARATE_50_HZ: Serial.println("50 Hz"); break;
    case LIS331_DATARATE_100_HZ: Serial.println("100 Hz"); break;
    case LIS331_DATARATE_400_HZ: Serial.println("400 Hz"); break;
    case LIS331_DATARATE_1000_HZ: Serial.println("1000 Hz"); break;
    case LIS331_DATARATE_LOWPOWER_0_5_HZ: Serial.println("0.5 Hz Low Power"); break;
    case LIS331_DATARATE_LOWPOWER_1_HZ: Serial.println("1 Hz Low Power"); break;
    case LIS331_DATARATE_LOWPOWER_2_HZ: Serial.println("2 Hz Low Power"); break;
    case LIS331_DATARATE_LOWPOWER_5_HZ: Serial.println("5 Hz Low Power"); break;
    case LIS331_DATARATE_LOWPOWER_10_HZ: Serial.println("10 Hz Low Power"); break;

  }



  Serial.println("Adafruit VCNL4040 Config demo");

  if (!vcnl4040.begin()) {
    Serial.println("Couldn't find VCNL4040 chip");
    while (1);
  }
  Serial.println("Found VCNL4040 chip");
}

void loop() {

  // 4 touch pins
  for (int i = 0; i < num_of_touch_pins; i++) touch_values[i] = touchRead(touch_pins[i]);
  Serial.print("touch_values: ");
  for (int i = 0; i < (num_of_touch_pins); i++) {
    Serial.print(touch_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");


  // photocell via analog pin 0

  for (int i = 0; i < num_of_analog_pins; i++) analog_values[i] = analogRead(analog_pins[i]);

  Serial.print("analog_values: ");
  for (int i = 0; i < (num_of_analog_pins); i++) {
    Serial.print(analog_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

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
  Serial.println(" ");

// accelerometer


  /* Get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2) */
  float xval = event.acceleration.x;
  Serial.print("x: "); 
  Serial.print(xval);
  Serial.print(" ");
  Serial.println(" ");
  
  float yval = event.acceleration.y;
  Serial.print("y: "); 
  Serial.print(yval);
  Serial.print(" ");
  Serial.println(" ");

  float zval = event.acceleration.z;
  Serial.print("z: "); 
  Serial.print(zval);
  Serial.print(" ");
  Serial.println(" ");
  
  delay(50);
}
