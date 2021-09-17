
void setupScreen() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  currentScreen = CALIBRATION;
}

void header(String name) {
  display.clearDisplay();
  display.setCursor(0, 8);
  display.print(name);

  if (trackingInProgress) {
    display.setCursor(112, 8);
    display.print(F("T"));
  }

  if (isGPSReady()) {
    display.setCursor(120, 8);
    display.print(F("G"));
  }
}

void updateScreen() {
  if (currentScreen == MENU) {
    showMenuPage();
  } if (currentScreen == GPS) {
    showGPSPage();
  } else if (currentScreen == NUNCHUK) {
    showNunchukTestPage();
  } else if (currentScreen == OBJECT_TYPE_CHOOSING) {
    showObjectTypeChoosingPage();
  } else if (currentScreen == OBJECT_CHOOSING) {
    showObjectChoosingPage();
  } else if (currentScreen == OBJECT_TRACKING) {
    showObjectTrackingPage();
  }else if (currentScreen == VISIBILITY) {
    showVisibilityPage();
  }else if (currentScreen == CALIBRATION) {
    showCalibrationPage();
  }

  display.display();
}
