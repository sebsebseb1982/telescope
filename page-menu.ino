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
    currentScreen = GPS;
    zButtonEventAlreadyTreated = true;
  }
}
