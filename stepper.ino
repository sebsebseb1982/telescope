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
  elevationStepper.setMaxSpeed(30000);
  elevationStepper.setAcceleration(28000);
}

void loopSteppers(long angleInDegrees) {
  elevationStepper.moveTo(angleInDegrees * elevationStepperSpecs.pulsesByRevolution / 360);
  elevationStepper.runToPosition();
}
