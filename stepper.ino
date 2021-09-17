#define speed 3000
AccelStepper azimuthMotor = AccelStepper(
                              1, // Interface
                              15, // Pulse pin
                              13 // Direction pin
                            );

TelescopeStepper azimuthStepper = {
  azimuthMotor,
  1600, // Pulse by revolution
  0
};

AccelStepper altitudeMotor = AccelStepper(
                               1, // Interface
                               0, // Pulse pin
                               2 // Direction pin
                             );

TelescopeStepper altitudeStepper = {
  altitudeMotor,
  1600, // Pulse by revolution
  0
};

MultiStepper telescopeSteppers;

void setupSteppers() {
  azimuthMotor.setMaxSpeed(speed);
  azimuthMotor.setAcceleration(speed);
  azimuthMotor.setSpeed(speed);
  altitudeMotor.setMaxSpeed(speed);
  altitudeMotor.setAcceleration(speed);
  altitudeMotor.setSpeed(speed);

  telescopeSteppers.addStepper(azimuthMotor);
  telescopeSteppers.addStepper(altitudeMotor);
}

void angleStepper(double azimuthInDegrees, double altitudeInDegrees) {
  //if (angleInDegrees != previousAzimuthAngle) {
  
    long positions[2]; // Array of desired stepper positions

    positions[0] = (azimuthInDegrees * azimuthStepper.pulsesByRevolution / 360)*10;
    positions[1] = (altitudeInDegrees * altitudeStepper.pulsesByRevolution / 360)*10;
    Serial.print(F("positions[0] : "));
    Serial.println(positions[0]);
    Serial.print(F("positions[1] : "));
    Serial.println(positions[1]);
    telescopeSteppers.moveTo(positions);
    telescopeSteppers.runSpeedToPosition(); // Blocks until all are in position
  
  /*azimuthMotor.moveTo(azimuthInDegrees * azimuthStepper.pulsesByRevolution / 360);
  azimuthMotor.runSpeed();
  altitudeMotor.moveTo(altitudeInDegrees * altitudeStepper.pulsesByRevolution / 360);
  altitudeMotor.runSpeed();
  */
  //}
}
/*
  void turnStepper(int delta) {
  azimuthStepper.move(delta);
  azimuthStepper.runToPosition();
  }
*/
