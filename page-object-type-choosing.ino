int selectedObjectTypeIndex = 0;
ObjectType selectedObjectType = objectTypes[selectedObjectTypeIndex];
const int nbObjectTypes = sizeof(objectTypes) / sizeof(ObjectType);

void showObjectTypeChoosingPage() {
  header("Tracking");

  display.setCursor(5, 55);

  int imageXPosition = 14;
  int imageYPosition = 14;

  if (selectedObjectType == MOON) {
    display.drawBitmap(
      imageXPosition,
      imageYPosition + 2,
      moon,
      100,
      50,
      WHITE
    );
    display.print(F("Moon"));
  } else if (selectedObjectType == PLANETS) {
    display.drawBitmap(
      imageXPosition,
      imageYPosition - 2,
      saturn,
      100,
      50,
      WHITE
    );
    display.print(F("Planets"));
  } else if (selectedObjectType == DEEP_SKY) {
    display.drawBitmap(
      imageXPosition,
      imageYPosition - 2,
      cluster,
      100,
      50,
      WHITE
    );
    display.print(F("Deep-sky"));
  } else if (selectedObjectType == ISS) {
    display.drawBitmap(
      imageXPosition,
      imageYPosition - 1,
      iss,
      100,
      50,
      WHITE
    );
    display.print(F("ISS"));
  }

  computeObjectTypeChoosingControls();
}

void computeObjectTypeChoosingControls() {

  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.zButton && !zButtonEventAlreadyTreated && !selectedObjectBelowHorizon) {
    currentScreen = OBJECT_CHOOSING;
    zButtonEventAlreadyTreated = true;
  }

  if (nunchukStatus.joystickDirection == LEFT && !joystickEventAlreadyTreated) {
    selectedObjectTypeIndex --;
    joystickEventAlreadyTreated = true;
  } else if (nunchukStatus.joystickDirection == RIGHT && !joystickEventAlreadyTreated) {
    selectedObjectTypeIndex ++;
    joystickEventAlreadyTreated = true;
  }

  if (selectedObjectTypeIndex == -1) {
    selectedObjectTypeIndex = nbObjectTypes - 1;
  } else {
    selectedObjectTypeIndex = selectedObjectTypeIndex % nbObjectTypes;
  }

  selectedObjectType = objectTypes[selectedObjectTypeIndex];

}
