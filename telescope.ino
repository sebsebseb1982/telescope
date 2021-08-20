/*******************************************************************
    A sample project for an printing the inputs
    from a nunchuck controller to serial.
    Works on both ESP8266 and ESP32
    Parts:
    D1 Mini ESP8266 * - http://s.click.aliexpress.com/e/uzFUnIe
 *  * = Affilate
    If you find what I do usefuland would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/
    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/
 // https://www.instructables.com/Arduino-Star-Finder-for-Telescopes/

#include <AccelStepper.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define dirPin 11
#define stepPin 12
#define motorInterfaceType 1

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);



// ----------------------------
// Standard Libraries
// ----------------------------

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <NintendoExtensionCtrl.h>
// This library is for interfacing with the Nunchuck

// Can be installed from the library manager
// https://github.com/dmadison/NintendoExtensionCtrl

Nunchuk nchuk;

// print values to serial every second
#define PRINT_DELAY 1000

void setup() {
  Serial.begin(115200);
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(1000);
  stepper.setAcceleration(1000);
  // The D1 Nunchuck shield uses the deafault i2c pins
  // SCL == D1 == GPIO5
  // SDA == D2 == GPIO4
  // The address of the nunchuck is 0x52

  nchuk.begin();
  while (!nchuk.connect()) {
    Serial.println("Nunchuk not detected!");
    delay(1000);
  }



  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
}

void loop() {
     stepper.runSpeed();

  Serial.println("----- Nunchuk Test -----"); // Making things easier to read

  boolean success = nchuk.update();  // Get new data from the controller

  if (!success) {  // Ruh roh
    Serial.println("Controller disconnected!");
    delay(10);
  }
  else {

    // -------------------
    // Buttons
    // -------------------

    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();

    Serial.print("Buttons pressed: ");
    if (zButton) {
      Serial.print("z");
    }

    if (cButton) {
      Serial.print("c");
    }
    Serial.println("");

    // -------------------
    // Joystick
    // -------------------

    // Read the joystick axis (0-255)
    // Note: I havent seen it go near 0 or 255
    // I've seen ranges closer to 30-210
    int joyY = nchuk.joyY();
    int joyX = nchuk.joyX();

    Serial.print("Joystick Value (x,y): ");
    Serial.print(joyX);
    Serial.print(",");
    Serial.println(joyY);

    // -------------------
    // Joystick
    // -------------------


    // Read the accelerometer (0-1023)
    int accelX = nchuk.accelX();
    int accelY = nchuk.accelY();
    int accelZ = nchuk.accelZ();

    Serial.print("Accelerometer Value (x,y,z): ");
    Serial.print(accelX);
    Serial.print(",");
    Serial.print(accelY);
    Serial.print(",");
    Serial.println(accelZ);

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    // Display static text
    display.print("x = ");  display.println(joyX);
    display.print("y = ");      display.println(joyY);

    int deltaX = joyX - 128;
    int deltaY = joyY - 128;
    double rad = atan2 (deltaY, deltaX); // In radians

    // For conversion to degrees you use the following formula:
    double deg = (rad * 57.295779513082320876798154814105) + 180;
    display.print("angle = ");      display.println(deg);

    //display.drawPixel(joyX/4, 64-(joyY/4), WHITE);

    int speed = (joyX - 128) * 100;
    display.print("speed = ");      display.println(speed);
    display.display();


/*
stepper.moveTo(stepper.currentPosition()+1000000);
    stepper.setSpeed(speed);


    stepper.run();*/
  }
}
