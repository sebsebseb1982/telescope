HorizontalCoordinate currentTrackedObject;

void track(EquatorialCoordinate objectToTrack) {
  currentTrackedObject = getHorizontalCoordinateFromEquatorialCoordinate(objectToTrack);
  angleStepper(currentTrackedObject.azimuth);
}
