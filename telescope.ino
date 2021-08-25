#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

#include "BigNumber.h"
// #include "MemoryFree.h"

#include "celestial-calculation.h"
#include "nunchuk.h"
#include "stepper.h"

static const int precision = 50;

void setup() {
  Serial.begin(115200);
  setupMath(precision);
  setupNunchuk();
  setupGPS();
  //setupSteppers();
  setupScreen();
}

void loop() {

  NunchukStatus nunchuckStatus = getNunchukStatus();
  int deltaX = nunchuckStatus.joystickX - 128;
  int deltaY = nunchuckStatus.joystickY - 128;
  double rad = atan2 (deltaY, deltaX); // In radians

  // For conversion to degrees you use the following formula:
  double deg = (rad * 57.295779513082320876798154814105) + 180;


  if (isGPSReady()) {
    TinyGPSPlus gps = getGPSDatas();
    //showGPSPage(gps);
    showNunchukTestPage(nunchuckStatus);

    EquatorialCoordinate whirpoolGalaxy = {
      202.46963,
      47.19519
    };

    EquatorialCoordinate pleiadeCluster = {
      56.87117,
      24.10503
    };

    HorizontalCoordinate horizontalCoordinate = getHorizontalCoordinateFromEquatorialCoordinate(whirpoolGalaxy, gps);

    //angleStepper(horizontalCoordinate.azimuth);
    showHorizontalCoordinates(horizontalCoordinate);

  }

  /*
    BigNumber testSinus = sinus(BigNumber("3.141592653589793238462643") / BigNumber(4), precision);
    printBignum("sinus(PI/4)", testSinus);
  */
  /*
        Serial.print("freeMemory()=");
      Serial.println(freeMemory());
  */
  //testTrigo();
  Serial.println("======================================================================================================");
  //delay(1000);
}
