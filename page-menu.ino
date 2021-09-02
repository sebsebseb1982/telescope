Screen menuContent[] = {
  OBJECT_CHOOSING,
  CALIBRATION,
  GPS,
  NUNCHUK,
  VISIBILITY
};

int selectedScreenIndex = 0;
Screen selectedScreen = menuContent[selectedScreenIndex];

void showMenuPage() {
  header("Menu");

  display.setCursor(0, 50);
  if (selectedScreen == GPS) {
    display.print(F("GPS"));
  } else if (selectedScreen == NUNCHUK) {
    display.print(F("Nunchuk"));
  } else if (selectedScreen == OBJECT_CHOOSING) {
    display.print(F("Object choosing"));
  } else if (selectedScreen == VISIBILITY) {
    display.print(F("Visibility"));
  } else if (selectedScreen == CALIBRATION) {
    display.print(F("Calibration"));
  }

  computeMenuPageControls();
}

void computeMenuPageControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();
  if (nunchukStatus.zButton && !zButtonEventAlreadyTreated) {
    currentScreen = selectedScreen;
    zButtonEventAlreadyTreated = true;
  }

  if (nunchukStatus.joystickDirection == LEFT && !joystickEventAlreadyTreated) {
    selectedScreenIndex --;
    joystickEventAlreadyTreated = true;
  } else if (nunchukStatus.joystickDirection == RIGHT && !joystickEventAlreadyTreated) {
    selectedScreenIndex ++;
    joystickEventAlreadyTreated = true;
  }

  int nbMenuContent = sizeof(menuContent) / sizeof(Screen);

  if (selectedScreenIndex == -1) {
    selectedScreenIndex = nbMenuContent - 1;
  } else {
    selectedScreenIndex = selectedScreenIndex % nbMenuContent;
  }

  selectedScreen = menuContent[selectedScreenIndex];
}
