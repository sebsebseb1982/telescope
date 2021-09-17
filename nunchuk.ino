#include <NintendoExtensionCtrl.h>

static const int joystickCenterValue = 128;
static const int deadZone = 20;

Nunchuk nunchuk;
boolean zButtonEventAlreadyTreated;
boolean cButtonEventAlreadyTreated;
boolean joystickEventAlreadyTreated;

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
/*


  NunchukStatus nunchuckStatus = getNunchukStatus();
  int deltaX = nunchuckStatus.joystickX - 128;
  int deltaY = nunchuckStatus.joystickY - 128;
  double rad = atan2 (deltaY, deltaX); // In radians

  // For conversion to degrees you use the following formula:
  double deg = (rad * 57.295779513082320876798154814105) + 180;

*/
NunchukStatus getNunchukStatus() {
  boolean success = nunchuk.update();
  if (!success) {  // Ruh roh
    Serial.println("Controller disconnected!");
  }

  if (!nunchuk.buttonZ()) {
    zButtonEventAlreadyTreated = false;
  }

  if (!nunchuk.buttonC()) {
    cButtonEventAlreadyTreated = false;
  }

  JoystickDirection joystickDirection = getJoystickDirection();
  if (joystickDirection == NONE) {
    joystickEventAlreadyTreated = false;
  }

//nunchuk.printDebug();

  return {
    nunchuk.buttonZ(),
    nunchuk.buttonC(),
    joystickDirection,
    nunchuk.joyX() - joystickCenterValue,
    nunchuk.joyY() - joystickCenterValue,
    nunchuk.accelX(),
    nunchuk.accelY(),
    nunchuk.accelZ()
  };
}

void computeControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.zButton && nunchukStatus.cButton) {
    currentScreen = MENU;
  }
}
