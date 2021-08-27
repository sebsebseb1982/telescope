#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

#include "BigNumber.h"
// #include "MemoryFree.h"

#include "celestial-calculation.h"
#include "object.h"
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
boolean trackingInProgress = false;
Object objects[] = {
  {
    "Whirpool galaxy",
    {
      202.46963,
      47.19519
    }
  },
  {
    "Pleiade cluster",
    {
      56.87117,
      24.10503
    }
  },
  {
    "47 TUCANAE, CLST",
    {
      6.02363,
      -72.08128
    }
  },
  {
    "BEEHIVE CLUSTER",
    {
      130.1,
      19.98333
    }
  },
  {
    "HYADES CLUSTER",
    {
      66.75,
      15.86667
    }
  },
  {
    "JEWEL BOX, CLSTR",
    {
      193.41254,
      -60.36161
    }
  },
  {
    "M4 CLUSTER",
    {
      245.89775,
      -26.52536
    }
  },
  {
    "M12 CLUSTER",
    {
      251.81042,
      -1.94781
    }
  },
  {
    "M14 CLUSTER",
    {
      264.40063,
      -3.24594
    }
  },
  {
    "M15 CLUSTER",
    {
      322.49375,
      12.16681
    }
  },
  {
    "M52 CLUSTER",
    {
      351.20504,
      61.59994
    }
  },
  {
    "M68 CLUSTER",
    {
      189.86675,
      -26.74281
    }
  },
  {
    "M93 CLUSTER",
    {
      116.12342,
      -23.85483
    }
  },
  {
    "M107 CLUSTER",
    {
      248.13279,
      -13.05356
    }
  },
  {
    "NGC 3201 CLUSTER",
    {
      154.40329,
      -46.41103
    }
  },
  {
    "NGC 4833 CLUSTER",
    {
      194.89567,
      -70.87453
    }
  },
  {
    "OMEGA CEN., CLST",
    {
      201.69142,
      -47.47681
    }
  },
  {
    "PLEIADES CLUSTER",
    {
      56.87117,
      24.10503
    }
  },
  {
    "CAT'S EYE NEBULA",
    {
      269.63917,
      66.63314
    }
  },
  {
    "CONE NEBULA",
    {
      100.24271,
      9.89558
    }
  },
  {
    "CRESCENT NEBULA",
    {
      303.02700,
      38.35497
    }
  },
  {
    "DUMBBELL NEBULA",
    {
      299.90133,
      22.72150
    }
  },
  {
    "EAGLE NEBULA",
    {
      274.70021,
      -13.80694
    }
  },
  {
    "EIGHT-BURST, NEB",
    {
      151.75675,
      -40.43619
    }
  },
  {
    "ESKIMO NEBULA",
    {
      112.29492,
      20.91175
    }
  },
  {
    "ETA CARINAE, NEB",
    {
      161.27513,
      -59.86661
    }
  },
  {
    "HELIX NEBULA",
    {
      337.41025,
      -20.83686
    }
  },
  {
    "HOURGLASS NEBULA",
    {
      204.89583,
      -67.38083
    }
  },
  {
    "IC 2944 NEBULA",
    {
      173.94717,
      -63.01936
    }
  },
  {
    "LAGOON NEBULA",
    {
      270.92504,
      -24.38
    }
  },
  {
    "ORION NEBULA",
    {
      83.82163,
      -5.39081
    }
  },
  {
    "OWL NEBULA",
    {
      168.69875,
      55.01914
    }
  },
  {
    "RING NEBULA",
    {
      283.39588,
      33.02914
    }
  },
  {
    "SATURN NEBULA",
    {
      316.04513,
      -11.36342
    }
  },
  {
    "STINGRAY NEBULA",
    {
      259.08780,
      -59.4899
    }
  },
  {
    "TARANTULA NEBULA",
    {
      84.67621,
      -69.10064
    }
  },
  {
    "TRIFID NEBULA",
    {
      270.63104,
      -22.99944
    }
  },
  {
    "VEIL NEBULA",
    {
      311.42513,
      30.71664
    }
  },
  {
    "ANDROMEDA GALAXY",
    {
      10.68471,
      41.26892
    }
  },
  {
    "BLACK EYE GALAXY",
    {
      194.18217,
      21.68186
    }
  },
  {
    "BODE'S GALAXY",
    {
      148.88813,
      69.06533
    }
  },
  {
    "CIGAR GALAXY",
    {
      148.96796,
      69.67983
    }
  },
  {
    "LARGE MAGELLANIC",
    {
      80.89433,
      -69.75611
    }
  },
  {
    "SMALL MAGELLANIC",
    {
      13.15838,
      -72.80028
    }
  },
  {
    "SOMBRERO GALAXY",
    {
      189.99775,
      -11.62294
    }
  },
  {
    "TRIANGULUM, GLXY",
    {
      23.46213,
      30.65986
    }
  }
};

void setup() {
  Serial.begin(115200);
  setupMath(precision);
  setupNunchuk();
  setupGPS();
  setupSteppers();
  setupScreen();
  setupTracker();
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

    track();
  }

  updateScreen();
  Serial.println(" == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ");
}
