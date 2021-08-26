#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

#include "BigNumber.h"
// #include "MemoryFree.h"

#include "celestial-calculation.h"
#include "nunchuk.h"
#include "stepper.h"
#include "screen.h"

static const int precision = 50;
TinyGPSPlus gps;
Screen currentScreen;

void setup() {
  Serial.begin(115200);
  setupMath(precision);
  setupNunchuk();
  setupGPS();
  //setupSteppers();
  setupScreen();
}

void loop() {

  refreshGPS();
  computeControls();
  if (isGPSReady()) {

    EquatorialCoordinate whirpoolGalaxy = {
      202.46963,
      47.19519
    };

    EquatorialCoordinate pleiadeCluster = {
      56.87117,
      24.10503
    };

    track(whirpoolGalaxy);

    //angleStepper(horizontalCoordinate.azimuth);
  }

  updateScreen();
  Serial.println("======================================================================================================");
}
