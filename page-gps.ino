void showGPSPage() {
  header("GPS");

  display.setCursor(0, 20);

  display.print(F("Lat. : "));
  display.println(gps.location.lat(), 6);
  display.print(F("Lon. : "));
  display.println(gps.location.lng(), 6);

  display.print(F("Date : "));
  display.print(gps.date.day());
  display.print(F("/"));
  display.print(gps.date.month());
  display.print(F("/"));
  display.println(gps.date.year());

  display.print(F("Time : "));
  if (gps.time.hour() < 10) display.print(F("0"));
  display.print(gps.time.hour());
  display.print(F(":"));
  if (gps.time.minute() < 10) display.print(F("0"));
  display.print(gps.time.minute());
  display.print(F(":"));
  if (gps.time.second() < 10) display.print(F("0"));
  display.print(gps.time.second());
  display.println(F("(UTC)"));

  display.print(F("Satellites :"));
  display.println(gps.satellites.value());
  /*
    // Display static text
    display.print("x = ");  display.println(nunchukStatus.joystickX);
    display.print("y = ");      display.println(nunchukStatus.joystickY);

    int deltaX = nunchukStatus.joystickX - 128;
    int deltaY = nunchukStatus.joystickY - 128;
    double rad = atan2 (deltaY, deltaX); // In radians

    // For conversion to degrees you use the following formula:
    double deg = (rad * 57.295779513082320876798154814105) + 180;
    display.print("angle = ");      display.println(deg);

    //display.drawPixel(joyX/4, 64-(joyY/4), WHITE);

    int speed = (nunchukStatus.joystickX - 128) * 100;
    display.print("speed = ");      display.println(speed);
  */
}
