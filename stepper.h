struct TelescopeStepper {
  AccelStepper motor;
  int pulsesByRevolution;
  double previousStep;
};
