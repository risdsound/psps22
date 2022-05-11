#define NUMBYTES 2 // number of bytes sent by Pd in a "packet"
int incomingByte[NUMBYTES];


// touch values array size, must be constant
const int num_of_touch_pins = 6; // total numer of analog pins
int touch_values[num_of_touch_pins];
int touch_pins[] = {
  0, 1, 3, 4, 15, 16 // list each touch pin to use
};

void setup() {

  pinMode(6, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // digital output, assign pin and value from Pd

  // look for 2 bytes of data and write them
  if (Serial.available() > 1) {
    for ( int i = 0; i < 2; i++) {
      incomingByte[i] = Serial.read();
    }
    digitalWrite(incomingByte[0], incomingByte[1]);
  }

  for (int i = 0; i < num_of_touch_pins; i++) touch_values[i] = touchRead(touch_pins[i]);
  Serial.print("touch_values: ");
  for (int i = 0; i < (num_of_touch_pins); i++) {
    Serial.print(touch_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  delay (20);
}
