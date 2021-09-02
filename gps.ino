static const uint32_t GPSBaud = 9600;

SoftwareSerial gpsSerial(12, 14);

void setupGPS() {
  gpsSerial.begin(GPSBaud);
  Serial.print(F("TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
}

void refreshGPS() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}

boolean isGPSReady() {
  refreshGPS();
  return gps.location.isValid() && gps.date.isValid() && gps.time.isValid();
}
