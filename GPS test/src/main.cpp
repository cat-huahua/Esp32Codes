// Requires TinyGPSPlus library (TinyGPSPlus by Mikal Hart)
// In Arduino IDE: Sketch -> Include Library -> Manage Libraries -> search "TinyGPSPlus"

#include <TinyGPS++.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial SerialGPS(2); // Use UART2

const int RXPin = 16; // ESP32 RX2 (connect to GPS TX)
const int TXPin = 17; // ESP32 TX2 (connect to GPS RX)
const uint32_t GPSBaud = 9600;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("NEO-6M + ESP32 example");
  SerialGPS.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
}

void loop() {
  // Feed GPS characters into TinyGPS++ parser
  while (SerialGPS.available() > 0) {
    char c = SerialGPS.read();
    gps.encode(c);
  }

  // When a new location is available, print some useful info
  if (gps.location.isUpdated()) {
    Serial.print("Lat: "); Serial.println(gps.location.lat(), 6);
    Serial.print("Lng: "); Serial.println(gps.location.lng(), 6);
    if (gps.altitude.isValid()) {
      Serial.print("Alt: "); Serial.print(gps.altitude.meters()); Serial.println(" m");
    }
    Serial.print("Sats: "); Serial.println(gps.satellites.value());
    if (gps.time.isValid()) {
      Serial.print("Time (UTC): ");
      if (gps.time.hour() < 10) Serial.print('0');
      Serial.print(gps.time.hour()); Serial.print(':');
      if (gps.time.minute() < 10) Serial.print('0');
      Serial.print(gps.time.minute()); Serial.print(':');
      if (gps.time.second() < 10) Serial.print('0');
      Serial.println(gps.time.second());
    }
    Serial.println();
  }
}