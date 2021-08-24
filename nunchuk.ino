#include <NintendoExtensionCtrl.h>

static const int joystickCenterValue = 128;
static const int deadZone = 20;

Nunchuk nunchuk;

void setupNunchuk() {
  nunchuk.begin();
  while (!nunchuk.connect()) {
    Serial.println("Nunchuk not detected !");
    delay(1000);
  }
}

JoystickDirection getJoystickDirection() {
  int zeroCenteredJoyX = nunchuk.joyX() - joystickCenterValue;
  int zeroCenteredJoyY = nunchuk.joyY() - joystickCenterValue;

  if (zeroCenteredJoyX < deadZone * -1 && abs(zeroCenteredJoyX) > abs(zeroCenteredJoyY)) {
    return LEFT;
  } else if (zeroCenteredJoyX > deadZone && abs(zeroCenteredJoyX) > abs(zeroCenteredJoyY)) {
    return RIGHT;
  } else if (zeroCenteredJoyY < deadZone * -1 && abs(zeroCenteredJoyY) > abs(zeroCenteredJoyX)) {
    return DOWN;
  } else if (zeroCenteredJoyY > deadZone && abs(zeroCenteredJoyY) > abs(zeroCenteredJoyX)) {
    return UP;
  } else {
    return NONE;
  }
}

NunchukStatus getNunchukStatus() {
  boolean success = nunchuk.update();
  if (!success) {  // Ruh roh
    Serial.println("Controller disconnected!");
  }

  return {
    nunchuk.buttonZ(),
    nunchuk.buttonC(),
    getJoystickDirection(),
    nunchuk.joyX() - joystickCenterValue,
    nunchuk.joyY() - joystickCenterValue,
    nunchuk.accelX(),
    nunchuk.accelY(),
    nunchuk.accelZ()
  };
}

boolean isNunchukLeft() {

}
