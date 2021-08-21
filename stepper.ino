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
  elevationStepper.setAcceleration(30000);
}

void loopSteppers(int destinationSteps) {
  elevationStepper.runToNewPosition(destinationSteps);
}
