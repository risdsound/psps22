//Wifi and OSC
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

// sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

char ssid[] = "networkSSID";      // network SSID (name), need to use this network because it does not require username, SAS computer needs to be on same network
char pass[] = "networkPWD";          // network password, check RISD ITS site, password may change periodically

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(127, 0, 0, 1);     // IP address of SAS computer, may change occasionally check System Preferences > Network > WiFi
const unsigned int outPort = 8000;          // remote port to receive OSC
const unsigned int localPort = 9000;        // local port to listen for OSC packets (actually not used for sending)


#define BNO055_SAMPLERATE_DELAY_MS (50)

Adafruit_BNO055 bno = Adafruit_BNO055();

void setup(void) {

  Serial.begin(115200);
  Serial.println("Orientation Sensor"); Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);

  /* Use external crystal for better accuracy */
  bno.setExtCrystalUse(true);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass); //

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  //Serial.println(Udp.localPort());

  delay(1000);

}

void loop(void) {


  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  float y = map(((float)event.orientation.x), 0., 360., -180., 180.);
  float p = map(((float)event.orientation.y), -90., 90., -180, 180.);
  float r = ((float)event.orientation.z);

  OSCMessage msg("/ypr");
  msg.add(y);
  msg.add(p);
  msg.add(r);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();

  delay(BNO055_SAMPLERATE_DELAY_MS);

}
