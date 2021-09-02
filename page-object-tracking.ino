

void showObjectTrackingPage() {
  header(currentTrackedObject.name);

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

double getDeltaValue() {
  NunchukStatus nunchukStatus = getNunchukStatus();
  if (nunchukStatus.cButton) {
    return 1.0;
  } else {
    return 0.1;
  }
}

void computeObjectTrackingControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.zButton && !zButtonEventAlreadyTreated && !nunchukStatus.cButton) {
    zButtonEventAlreadyTreated = true;
    trackingInProgress = !trackingInProgress;
  }

  if (nunchukStatus.joystickDirection == LEFT) {
    deltaAzimuth += -1 * getDeltaValue();
  } else if (nunchukStatus.joystickDirection == RIGHT) {
    deltaAzimuth += getDeltaValue();
  } else if (nunchukStatus.joystickDirection == UP) {
    deltaAltitude += getDeltaValue();
  } else if (nunchukStatus.joystickDirection == DOWN) {
    deltaAltitude += -1 * getDeltaValue();
  }
}
