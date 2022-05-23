
/*
  this test for Myoware muscle sensor
  https://www.adafruit.com/product/2699

*/

int Signal;                

void setup() {
  Serial.begin(9600);         
}

// The Main Loop Function
void loop() {

  Signal = analogRead(A0);  // read from analog pin

  Serial.print("Myo: ");
  Serial.print(Signal);                   
  Serial.print(" ");
  Serial.println(" ");
 
  delay(20);

}
