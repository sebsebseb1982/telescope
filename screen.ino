#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupScreen() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void menu(String name) {
  display.clearDisplay();
  display.setCursor(0, 8);
  display.print(name);

  if (gps.satellites.isValid()) {
    TinyGPSPlus gps = getGPSDatas();
    display.setCursor(80, 8);
    display.print(F("Sat: "));
    display.print(gps.satellites.value());
  }
}

void showNunchukTestPage(NunchukStatus nunchuckStatus) {
  menu("Nunchuk test");

  display.setCursor(0, 20);
  display.print(F("Direction : "));
  if (nunchuckStatus.joystickDirection == UP) {
    display.println(F("UP"));
  } else if (nunchuckStatus.joystickDirection == DOWN) {
    display.println(F("DOWN"));
  } else if (nunchuckStatus.joystickDirection == LEFT) {
    display.println(F("LEFT"));
  } else if (nunchuckStatus.joystickDirection == RIGHT) {
    display.println(F("RIGHT"));
  } else {
    display.println(F("NONE"));
  }

  display.print(F("C button : "));
  if (nunchuckStatus.cButton) {
    display.println(true);
  } else {
    display.println(false);
  }

  display.print(F("Z button : "));
  if (nunchuckStatus.zButton) {
    display.println(true);
  } else {
    display.println(false);
  }
  
  display.display();
}

void showGPSPage(TinyGPSPlus gps) {
  menu("GPS");


  display.setCursor(0, 20);

  display.print(F("Lat.: "));
  display.println(gps.location.lat(), 6);
  display.print(F("Lon.: "));
  display.println(gps.location.lng(), 6);

  display.print(F("Date :"));
  display.print(gps.date.day());
  display.print(F("/"));
  display.print(gps.date.month());
  display.print(F("/"));
  display.println(gps.date.year());

  display.print(F("Heure: "));
  if (gps.time.hour() < 10) display.print(F("0"));
  display.print(gps.time.hour());
  display.print(F(":"));
  if (gps.time.minute() < 10) display.print(F("0"));
  display.print(gps.time.minute());
  display.print(F(":"));
  if (gps.time.second() < 10) display.print(F("0"));
  display.print(gps.time.second());
  display.println(F("(UTC)"));

  /*
    // Display static text
    display.print("x = ");  display.println(nunchuckStatus.joystickX);
    display.print("y = ");      display.println(nunchuckStatus.joystickY);

    int deltaX = nunchuckStatus.joystickX - 128;
    int deltaY = nunchuckStatus.joystickY - 128;
    double rad = atan2 (deltaY, deltaX); // In radians

    // For conversion to degrees you use the following formula:
    double deg = (rad * 57.295779513082320876798154814105) + 180;
    display.print("angle = ");      display.println(deg);

    //display.drawPixel(joyX/4, 64-(joyY/4), WHITE);

    int speed = (nunchuckStatus.joystickX - 128) * 100;
    display.print("speed = ");      display.println(speed);
  */
  display.display();
}

void showHorizontalCoordinates(HorizontalCoordinate horizontalCoordinates) {
  menu("Star");


  display.setCursor(0, 20);

  display.print(F("Az. : "));
  display.println(horizontalCoordinates.azimuth, 10);
display.print(F("Alt. : "));
  display.println(horizontalCoordinates.altitude, 10);
  /*
    // Display static text
    display.print("x = ");  display.println(nunchuckStatus.joystickX);
    display.print("y = ");      display.println(nunchuckStatus.joystickY);

    int deltaX = nunchuckStatus.joystickX - 128;
    int deltaY = nunchuckStatus.joystickY - 128;
    double rad = atan2 (deltaY, deltaX); // In radians

    // For conversion to degrees you use the following formula:
    double deg = (rad * 57.295779513082320876798154814105) + 180;
    display.print("angle = ");      display.println(deg);

    //display.drawPixel(joyX/4, 64-(joyY/4), WHITE);

    int speed = (nunchuckStatus.joystickX - 128) * 100;
    display.print("speed = ");      display.println(speed);
  */
  display.display();
}
