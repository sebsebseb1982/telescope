#define columnMaxHeight 20
#define columnBottomY 45
#define nbSectors 8

int sectorsVisibility[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int selectedSector = 0;

void drawSectors() {
  int sectorIndex = 0;
  while (sectorIndex < nbSectors) {
    int sectorX = sectorIndex * 16;
    int sectorVisibility = sectorsVisibility[sectorIndex];
    int columnHeight = max((columnMaxHeight * max(sectorVisibility, 1)) / 90, 1);

    display.fillRect(
      sectorX + 1,
      columnBottomY - columnHeight,
      14,
      columnHeight,
      WHITE
    );

    display.setCursor(sectorX + 2, 50);
    display.print(sectorVisibility);

    sectorIndex++;
  }

  display.fillCircle(
    (selectedSector * 16) + 8,
    20,
    2,
    WHITE
  );
}

void showVisibilityPage() {
  header("Visibility");

  display.setCursor(0, 20);
  drawSectors();
  computeVisibilityControls();
}

void computeVisibilityControls() {
  NunchukStatus nunchukStatus = getNunchukStatus();

  if (nunchukStatus.joystickDirection == LEFT && !joystickEventAlreadyTreated) {
    selectedSector --;
    joystickEventAlreadyTreated = true;
  } else if (nunchukStatus.joystickDirection == RIGHT && !joystickEventAlreadyTreated) {
    selectedSector ++;
    joystickEventAlreadyTreated = true;
  } else if (nunchukStatus.joystickDirection == UP) {
    sectorsVisibility[selectedSector] = min(sectorsVisibility[selectedSector] + 5, 90);
  } else if (nunchukStatus.joystickDirection == DOWN) {
    sectorsVisibility[selectedSector] = max(sectorsVisibility[selectedSector] - 5, 0);
  }

  if (selectedSector == -1) {
    selectedSector = nbSectors - 1;
  } else {
    selectedSector = selectedSector % nbSectors;
  }
}
