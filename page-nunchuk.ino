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
}
