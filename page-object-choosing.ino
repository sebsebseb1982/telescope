int selectedObjectIndex = 0;
Object selectedObject = objects[selectedObjectIndex];

void showObjectChoosingPage() {
  header("Tracking");

  display.setCursor(0, 40);
  display.println(selectedObject.name);

  computeObjectChoosingControls();
}

void computeObjectChoosingControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.zButton && !zButtonEventAlreadyTreated) {
    currentTrackedObject = selectedObject;
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

  int nbObjects = sizeof(objects) / sizeof(Object);

  if (selectedObjectIndex == -1) {
    selectedObjectIndex = nbObjects - 1;
  } else {
    selectedObjectIndex = selectedObjectIndex % nbObjects;
  }

  selectedObject = objects[selectedObjectIndex];
  /*
    else if (nunchukStatus.joystickDirection == UP && !joystickEventAlreadyTreated) {
      deltaAltitude += 0.1;
    } else if (nunchukStatus.joystickDirection == DOWN && !joystickEventAlreadyTreated) {
      deltaAltitude += -0.1;
    }
  */
}
