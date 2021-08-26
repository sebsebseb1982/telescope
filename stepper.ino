#include <AccelStepper.h>

Stepper azimuthStepperSpecs = {
  13,
  15,
  1,
  1600
};

AccelStepper azimuthStepper = AccelStepper(
                                  azimuthStepperSpecs.interfaceType,
                                  azimuthStepperSpecs.pulsePin,
                                  azimuthStepperSpecs.directionPin
                                );

void setupSteppers() {
  azimuthStepper.setMaxSpeed(1600);
  //azimuthStepper.setAcceleration(300);
}

void angleStepper(long angleInDegrees) {
  azimuthStepper.moveTo(angleInDegrees * azimuthStepperSpecs.pulsesByRevolution / 360);
  azimuthStepper.runToPosition();
}

void turnStepper(int delta) {
  azimuthStepper.move(delta);
  azimuthStepper.runToPosition();
}
