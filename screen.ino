
void setupScreen() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  currentScreen = MENU;
}

void header(String name) {
  display.clearDisplay();
  display.setCursor(0, 8);
  display.print(name);

  if (gps.satellites.isValid()) {
    display.setCursor(80, 8);
    display.print(F("Sat: "));
    display.print(gps.satellites.value());
  }
}

void updateScreen() {
  if (currentScreen == MENU) {
    showMenuPage();
  } if (currentScreen == GPS) {
    showGPSPage();
  } else if (currentScreen == NUNCHUK) {
    showNunchukTestPage();
  } else if (currentScreen == OBJECT_CHOOSING) {
    showObjectChoosingPage();
  }else if (currentScreen == OBJECT_TRACKING) {
    showObjectTrackingPage();
  }
  display.display();
}
