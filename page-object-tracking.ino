void showObjectTrackingPage() {
  header("Tracking");

  display.setCursor(0, 20);

  display.print(F("Az. : "));
  display.println(currentTrackedObject.azimuth, 10);
  display.print(F("Alt. : "));
  display.println(currentTrackedObject.altitude, 10);
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
