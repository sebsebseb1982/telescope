#include <SPI.h>
#include <Wire.h>

#include "nunchuk.h"
#include "stepper.h"

void setup() {
  Serial.begin(115200);
  setupNunchuk();
  setupSteppers();
  setupScreen();
}

void loop() {
  NunchukStatus nunchuckStatus = getNunchukStatus();
  int deltaX = nunchuckStatus.joystickX - 128;
  int deltaY = nunchuckStatus.joystickY - 128;
  double rad = atan2 (deltaY, deltaX); // In radians

  // For conversion to degrees you use the following formula:
  double deg = (rad * 57.295779513082320876798154814105) + 180;
  loopSteppers(deg);
  loopScreen();
}
