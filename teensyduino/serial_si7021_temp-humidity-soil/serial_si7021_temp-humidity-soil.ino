#include "Adafruit_Si7021.h"
#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(115200);

  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");

  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;

    if (!ss.begin(0x36)) {
      Serial.println("ERROR! seesaw not found");
      while (1) delay(1);
    } else {
      Serial.print("seesaw started! version: ");
      Serial.println(ss.getVersion(), HEX);
    }
  }

  Serial.print("Found model ");
  switch (sensor.getModel()) {
    case SI_Engineering_Samples:
      Serial.print("SI engineering samples"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }
  Serial.print(" Rev(");
  Serial.print(sensor.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor.sernum_a, HEX); Serial.println(sensor.sernum_b, HEX);
}

void loop() {

  // temperature sensor 
  
  float humid = sensor.readHumidity();
  Serial.print("humidity: ");
  Serial.print(humid);
  Serial.print(" ");
  Serial.println(" ");

  float temp = sensor.readTemperature();
  Serial.print("temperature: ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.println(" ");


  // soil sensor

  float tempC = ss.getTemp();
  Serial.print("soiltemp: "); 
  Serial.print(tempC);
  Serial.print(" ");
  Serial.println(" ");

  uint16_t capread = ss.touchRead(0);
  Serial.print("capacitive: ");
  Serial.print(capread);
  Serial.print(" ");
  Serial.println(" ");

  delay(1000);

  // Toggle heater enabled state every 30 seconds
  // An ~1.8 degC temperature increase can be noted when heater is enabled
  //  if (++loopCnt == 30) {
  //    enableHeater = !enableHeater;
  //    sensor.heater(enableHeater);
  //    Serial.print("Heater Enabled State: ");
  //    if (sensor.isHeaterEnabled())
  //      Serial.println("ENABLED");
  //    else
  //      Serial.println("DISABLED");
  //
  //    loopCnt = 0;
  //  }
}
