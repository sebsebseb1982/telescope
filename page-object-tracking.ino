

void showObjectTrackingPage() {
  header("Tracking");

  display.setCursor(0, 20);

  display.print(F("Az. : "));
  display.println(currentHorizontalCoordinate.azimuth, 3);
  display.print(F("Alt. : "));
  display.println(currentHorizontalCoordinate.altitude, 3);
  display.print(F("Delta az. : "));
  display.println(deltaAzimuth, 1);
  display.print(F("Delta alt. : "));
  display.println(deltaAltitude, 1);
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

  computeObjectTrackingControls();
}

void computeObjectTrackingControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.joystickDirection == LEFT && !joystickEventAlreadyTreated) {
    deltaAzimuth += -0.1;
  } else if (nunchukStatus.joystickDirection == RIGHT && !joystickEventAlreadyTreated) {
    deltaAzimuth += 0.1;
  }else if (nunchukStatus.joystickDirection == UP && !joystickEventAlreadyTreated) {
    deltaAltitude += 0.1;
  }else if (nunchukStatus.joystickDirection == DOWN && !joystickEventAlreadyTreated) {
    deltaAltitude += -0.1;
  }
}
