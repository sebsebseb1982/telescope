#include <SPI.h>
#include <Wire.h>

#include <TinyGPSPlus.h>

#include "celestial-calculation.h"
#include "nunchuk.h"
#include "stepper.h"

void setup() {
  Serial.begin(115200);
  setupNunchuk();
  setupGPS();
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
  //angleStepper(deg);
  if (nunchuckStatus.zButton) {
    turnStepper((nunchuckStatus.joystickX - 128) / 3);
  } else {
    turnStepper((nunchuckStatus.joystickX - 128) / 6);
  }

  if (isGPSReady()) {
    TinyGPSPlus gps = getGPSDatas();
    showGPSPage(gps);
    //showNunchukTestPage(nunchuckStatus);

    EquatorialCoordinate whirpoolGalaxy = {
      202.46963,
      47.19519
    };

    EquatorialCoordinate pleiadeCluster = {
      56.87117,
      24.10503
    };

    HorizontalCoordinate horizontalCoordinate = getHorizontalCoordinateFromEquatorialCoordinate(pleiadeCluster, gps);

    Serial.print(F(" Altitude : "));
    Serial.print(horizontalCoordinate.altitude, 10);

    Serial.print(F(" Azimuth : "));
    Serial.println(horizontalCoordinate.azimuth, 10);
  }



}
