#include <AccelStepper.h>

Stepper azimuthStepperSpecs = {
  13,
  15,
  1,
  1600
};
double previousAngle = 0;
AccelStepper azimuthStepper = AccelStepper(
                                azimuthStepperSpecs.interfaceType,
                                azimuthStepperSpecs.pulsePin,
                                azimuthStepperSpecs.directionPin
                              );

void setupSteppers() {
  azimuthStepper.setMaxSpeed(1600);
  azimuthStepper.setAcceleration(800);
  azimuthStepper.setSpeed(1600);
}

void angleStepper(double angleInDegrees) {
  if (angleInDegrees != previousAngle) {
    azimuthStepper.moveTo(angleInDegrees * azimuthStepperSpecs.pulsesByRevolution / 360);
    azimuthStepper.runToPosition();
    previousAngle = angleInDegrees;
  }
}

void turnStepper(int delta) {
  azimuthStepper.move(delta);
  azimuthStepper.runToPosition();
}
