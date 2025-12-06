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
  Serial.begin(9600);
  delay(100);
  Serial.println("NEO-6M + ESP32 example");
  SerialGPS.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
}

void loop() {
  while (SerialGPS.available() > 0) {
    char c = SerialGPS.read();
    gps.encode(c);
  

  if (gps.location.isUpdated()) {
    Serial.print("Latitude: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" Longitude: ");
    Serial.println(gps.location.lng(), 6);
    }
  }
}