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

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
static const int precision = 50;
TinyGPSPlus gps;
Screen currentScreen;

void setup() {
  Serial.begin(115200);
  setupMath(precision);
  setupNunchuk();
  setupGPS();
  setupSteppers();
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
  }

  updateScreen();
  Serial.println("======================================================================================================");
}
