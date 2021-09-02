int selectedObjectIndex = 0;
boolean selectedObjectBelowHorizon = false;
Object selectedObject = objects[selectedObjectIndex];
const int nbObjects = sizeof(objects) / sizeof(Object);

void showObjectChoosingPage() {
  header("Tracking");

  display.setCursor(0, 30);
  if (isGPSReady()) {
    display.print(selectedObjectIndex + 1);
    display.print(F("/"));
    display.println(nbObjects);
    display.println(selectedObject.name);
    HorizontalCoordinate selectedObjectHorizontalCoordinate = getHorizontalCoordinateFromEquatorialCoordinate(selectedObject.equatorialCoordinate);

    selectedObjectBelowHorizon = selectedObjectHorizontalCoordinate.altitude < 0;
    if (selectedObjectBelowHorizon) {
      display.println(F("Below horizon"));
    }

    computeObjectChoosingControls();
  } else {
    display.print(F("Waiting for GPS ..."));
  }
}

void computeObjectChoosingControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.zButton && !zButtonEventAlreadyTreated && !selectedObjectBelowHorizon) {
    currentTrackedObject = selectedObject;
    trackingInProgress = true;
    currentScreen = OBJECT_TRACKING;
    zButtonEventAlreadyTreated = true;
  }

  if (nunchukStatus.joystickDirection == LEFT && !joystickEventAlreadyTreated) {
    selectedObjectIndex --;
    joystickEventAlreadyTreated = true;
  } else if (nunchukStatus.joystickDirection == RIGHT && !joystickEventAlreadyTreated) {
    selectedObjectIndex ++;
    joystickEventAlreadyTreated = true;
  }

  if (selectedObjectIndex == -1) {
    selectedObjectIndex = nbObjects - 1;
  } else {
    selectedObjectIndex = selectedObjectIndex % nbObjects;
  }

  selectedObject = objects[selectedObjectIndex];
}
