void showNunchukTestPage() {
  header("Nunchuk");
  NunchukStatus nunchukStatus = getNunchukStatus();

  display.setCursor(0, 20);
  display.print(F("Direction : "));
  if (nunchukStatus.joystickDirection == UP) {
    display.println(F("UP"));
  } else if (nunchukStatus.joystickDirection == DOWN) {
    display.println(F("DOWN"));
  } else if (nunchukStatus.joystickDirection == LEFT) {
    display.println(F("LEFT"));
  } else if (nunchukStatus.joystickDirection == RIGHT) {
    display.println(F("RIGHT"));
  } else {
    display.println(F("NONE"));
  }

  display.print(F("Joy X : "));
  display.println(nunchukStatus.joystickX);
  display.print(F("Joy Y : "));
  display.println(nunchukStatus.joystickY);

  display.print(F("C button : "));
  if (nunchukStatus.cButton) {
    display.println(true);
  } else {
    display.println(false);
  }

  display.print(F("Z button : "));
  if (nunchukStatus.zButton) {
    display.println(true);
  } else {
    display.println(false);
  }

  display.drawRect(102, 38, 20, 20, WHITE);
  double rad = atan2 (nunchukStatus.joystickY, nunchukStatus.joystickX); // In radians
  double deg = (rad * 57.295779513082320876798154814105) + 180;
  uint16_t pixelX = 112 + (nunchukStatus.joystickX / 16.0);
  uint16_t pixelY = 48 - (nunchukStatus.joystickY / 16.0);
  display.drawPixel(pixelX, pixelY, WHITE);

}
