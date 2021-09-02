double calibrationAltitude = 0.0;
double calibrationAzimuth = 0.0;

void showCalibrationPage() {
  header("Calibration");

  display.setCursor(0, 20);

  display.println(F("Align with Polaris"));
  display.println(F("and press Z"));

  trackingInProgress = false;

  computeCalibrationControls();
}

double getCalibrationValue() {
  NunchukStatus nunchukStatus = getNunchukStatus();
  if (nunchukStatus.cButton) {
    return 1.0;
  } else {
    return 0.1;
  }
}

void computeCalibrationControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.zButton && !zButtonEventAlreadyTreated) {
    currentScreen = MENU;
    zButtonEventAlreadyTreated = true;
  }

  if (nunchukStatus.joystickDirection == LEFT) {
    calibrationAzimuth += -1 * getDeltaValue();
  } else if (nunchukStatus.joystickDirection == RIGHT) {
    calibrationAzimuth += getDeltaValue();
  } else if (nunchukStatus.joystickDirection == UP) {
    calibrationAltitude += getDeltaValue();
  } else if (nunchukStatus.joystickDirection == DOWN) {
    calibrationAltitude += -1 * getDeltaValue();
  }

  //angleStepper(calibrationAzimuth);
}
