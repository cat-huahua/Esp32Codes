/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-gps
 */

#include <TinyGPS++.h>

#define GPS_BAUDRATE 115200  // The default baudrate of NEO-6M is 9600

TinyGPSPlus gps;  // the TinyGPS++ object

void setup() {
  Serial.begin(115200);
  Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, 16, 17);

  Serial.println(F("ESP32 - GPS module"));
}

void loop() {
  if (Serial2.available() > 0) {
    Serial.write(Serial2.read());}


}