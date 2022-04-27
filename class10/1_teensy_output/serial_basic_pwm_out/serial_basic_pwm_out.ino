/*

  RISD CTC/DM-2001
  Programming Sound: Performance Systems
  Prof. Shawn Greenlee

  Teensy LC starter code

  For Teensy LC basic serial communition to Pure Data
  Code adapted from Alexandros Drymonits, Yann Seznec, and PJRC: public domain

*/

#define NUMBYTES 2 // number of bytes sent by Pd in a "packet"
int incomingByte[NUMBYTES];


// analog values array size, must be constant
const int num_of_analog_pins = 1; // total numer of analog pins
int analog_values[num_of_analog_pins];
int analog_pins[] = {
 0, // list each analog pin to use
};

// digital_values array size, must be constant
const int num_of_digital_pins = 1; // total numer of digital pins
int digital_values[num_of_digital_pins];
int digital_pins [] = {
  0, // list each digital pin to use
};


void setup() {

  // analogReadResolution(12); // Teensy is 12bit ADC, you can set to 12 but this will introduce some noise, also you can set lower like 7bit for MIDI range
  analogReadAveraging(32); // Teensy can do averaging of samples in hardware, set to 4, 8, 16, 32

  pinMode(0, INPUT_PULLUP);  // set pin modes individually
  //  pinMode(1, INPUT_PULLUP);
  //  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
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

  Serial.begin(9600);
}

void loop() {

// digital output, assign pin and value from Pd

  // look for 2 bytes of data and write them
  if (Serial.available() > 1) {
    for ( int i = 0; i < 2; i++) {
      incomingByte[i] = Serial.read();
    }
    analogWrite(incomingByte[0], incomingByte[1]);
  }


  for (int i = 0; i < num_of_analog_pins; i++) analog_values[i] = analogRead(analog_pins[i]);
  for (int i = 0; i < num_of_digital_pins; i++) digital_values[i] = !digitalRead(digital_pins[i]);


  Serial.print("analog_values: ");
  for (int i = 0; i < (num_of_analog_pins); i++) {
    Serial.print(analog_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");


  Serial.print("digital_values: ");
  for (int i = 0; i < (num_of_digital_pins); i++) {
    Serial.print(digital_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  delay(20);
}
