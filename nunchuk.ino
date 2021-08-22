#include <NintendoExtensionCtrl.h>

Nunchuk nunchuk;

void setupNunchuk() {
  nunchuk.begin();
  while (!nunchuk.connect()) {
    Serial.println("Nunchuk not detected !");
    delay(1000);
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
    nunchuk.joyX(),
    nunchuk.joyY(),
    nunchuk.accelX(),
    nunchuk.accelY(),
    nunchuk.accelZ()
  };
}