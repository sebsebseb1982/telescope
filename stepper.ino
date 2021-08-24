#include <AccelStepper.h>

Stepper elevationStepperSpecs = {
  11,
  12,
  1,
  1600
};

AccelStepper elevationStepper = AccelStepper(
                                  elevationStepperSpecs.interfaceType,
                                  elevationStepperSpecs.pulsePin,
                                  elevationStepperSpecs.directionPin
                                );

void setupSteppers() {
  elevationStepper.setMaxSpeed(1000);
  elevationStepper.setAcceleration(300);
}

void angleStepper(long angleInDegrees) {
  elevationStepper.moveTo(angleInDegrees * elevationStepperSpecs.pulsesByRevolution / 360);
  elevationStepper.runToPosition();
}

void turnStepper(int delta) {
  elevationStepper.move(delta);
  elevationStepper.runToPosition();
}
