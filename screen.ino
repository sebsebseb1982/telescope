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
}

void loopScreen() {
  display.clearDisplay();
/*
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
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
