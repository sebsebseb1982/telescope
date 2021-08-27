Object currentTrackedObject;
HorizontalCoordinate currentHorizontalCoordinate;

double deltaAzimuth = 0;
double deltaAltitude = 0;

void setupTracker() {
  currentTrackedObject = objects[0];
}

void track() {
  currentHorizontalCoordinate = getHorizontalCoordinateFromEquatorialCoordinate(currentTrackedObject.equatorialCoordinate);
  if (trackingInProgress) {
    angleStepper(currentHorizontalCoordinate.azimuth + deltaAzimuth);
  }
}
