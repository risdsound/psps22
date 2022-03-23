#include <Tlv493d.h>

// Tlv493d Opject
Tlv493d Tlv493dMagnetic3DSensor = Tlv493d();

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Tlv493dMagnetic3DSensor.begin();
  Tlv493dMagnetic3DSensor.setAccessMode(Tlv493dMagnetic3DSensor.MASTERCONTROLLEDMODE);
  Tlv493dMagnetic3DSensor.disableTemp();
}

void loop() {
  
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

  delay(20);
  
}
