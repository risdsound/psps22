/*
   Based on:
   Encoder Library - TwoKnobs Example
   http://www.pjrc.com/teensy/td_libs_Encoder.html

  Demo with Adafruit rotary encoder https://www.adafruit.com/product/377

*/

#include <Encoder.h>

Encoder knobLeft(5, 6);
Encoder knobRight(7, 8);

// digital_values array size, for push button of encoder
const int num_of_digital_pins = 2; // total numer of digital pins
int digital_values[num_of_digital_pins];
int digital_pins [] = {
  0, 1 // list each digital pin to use
};


void setup() {
  pinMode(0, INPUT_PULLUP); // encoder pushbutton
  pinMode(1, INPUT_PULLUP); // encoder pushbutton

  Serial.begin(9600);

}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {

    Serial.print("Left: ");
    Serial.print(newLeft);
    Serial.print(" ");
    Serial.println(" ");

    Serial.print("Right: ");
    Serial.print(newRight);
    Serial.print(" ");
    Serial.println(" ");

    positionLeft = newLeft; 
    positionRight = newRight;
  }
  for (int i = 0; i < num_of_digital_pins; i++) digital_values[i] = !digitalRead(digital_pins[i]);

  Serial.print("digital_values: "); // encoder pushbutton
  for (int i = 0; i < (num_of_digital_pins); i++) {
    Serial.print(digital_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  delay(20);
}
