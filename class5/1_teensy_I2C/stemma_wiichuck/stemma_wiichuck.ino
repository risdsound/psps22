#include <WiiChuck.h>

Accessory nunchuck;

void setup() {
  Serial.begin(9600);
  nunchuck.begin();
  if (nunchuck.type == Unknown) {
    nunchuck.type = NUNCHUCK;
  }
}

void loop() {
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
