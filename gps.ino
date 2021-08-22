static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

void setupGPS() {
  Serial1.begin(GPSBaud);
  Serial.print(F("TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
}

void refreshGPS() {
  while (Serial1.available() > 0)
    gps.encode(Serial1.read());

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

TinyGPSPlus getGPSDatas() {
    refreshGPS();
  return gps;
}
