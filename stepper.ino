#include <AccelStepper.h>

Stepper elevationStepperSpecs = {
  13,
  15,
  1,
  1600
};

AccelStepper elevationStepper = AccelStepper(
                                  elevationStepperSpecs.interfaceType,
                                  elevationStepperSpecs.pulsePin,
                                  elevationStepperSpecs.directionPin
                                );

void setupSteppers() {
  elevationStepper.setMaxSpeed(1600);
  //elevationStepper.setAcceleration(300);
}

void angleStepper(long angleInDegrees) {
  elevationStepper.moveTo(angleInDegrees * elevationStepperSpecs.pulsesByRevolution / 360);
  elevationStepper.runToPosition();
}

void turnStepper(int delta) {
  elevationStepper.move(delta);
  elevationStepper.runToPosition();
}
