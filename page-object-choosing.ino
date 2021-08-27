int selectedObjectIndex = 0;
Object selectedObject = objects[selectedObjectIndex];
const int nbObjects = sizeof(objects) / sizeof(Object);

void showObjectChoosingPage() {
  header("Tracking");

  display.setCursor(0, 30);
  display.print(selectedObjectIndex + 1);
  display.print(F("/"));
  display.println(nbObjects);
  display.println(selectedObject.name);
  HorizontalCoordinate selectedObjectHorizontalCoordinate = getHorizontalCoordinateFromEquatorialCoordinate(selectedObject.equatorialCoordinate);
  if (selectedObjectHorizontalCoordinate.altitude < 0) {
    display.println(F("Below horizon"));
  }

  computeObjectChoosingControls();
}

void computeObjectChoosingControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.zButton && !zButtonEventAlreadyTreated) {
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
