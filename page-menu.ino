Screen selectedScreen = GPS;

void showMenuPage() {
  header("Menu");

  display.setCursor(0, 50);
  if (selectedScreen == GPS) {
    display.print(F("GPS"));
  } else if (selectedScreen == NUNCHUK) {
    display.print(F("Nunchuk"));
  } else if (selectedScreen == OBJECT_TRACKING) {
    display.print(F("Object tracking"));
  }

  computeMenuPageControls();
}

void computeMenuPageControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();
  if (nunchukStatus.zButton && !zButtonEventAlreadyTreated) {
    currentScreen = selectedScreen;
    zButtonEventAlreadyTreated = true;
  }

  if (nunchukStatus.joystickDirection == LEFT /*&& !joystickEventAlreadyTreated*/) {
    joystickEventAlreadyTreated = true;
    selectedScreen = NUNCHUK;
  } else if (nunchukStatus.joystickDirection == RIGHT /*&& !joystickEventAlreadyTreated*/) {
    joystickEventAlreadyTreated = true;
    selectedScreen = OBJECT_TRACKING;
  } else {
    joystickEventAlreadyTreated = true;
    selectedScreen = GPS;
  }
}
