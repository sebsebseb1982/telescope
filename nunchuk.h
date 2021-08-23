enum JoystickDirection {
  LEFT, RIGHT, UP, DOWN, NONE
};

struct NunchukStatus {
  boolean zButton;
  boolean cButton;
  JoystickDirection joystickDirection;
  int joystickX;
  int joystickY;
  int accelerometerX;
  int accelerometerY;
  int accelerometerZ;
};
