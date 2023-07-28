#include "AccelStepper.h"

#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38
#define X_MIN_PIN 3
#define X_MAX_PIN 2

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
#define Y_MIN_PIN 14
#define Y_MAX_PIN 15

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62
#define Z_MIN_PIN 18
#define Z_MAX_PIN 19

#define E_STEP_PIN 26
#define E_DIR_PIN 28
#define E_ENABLE_PIN 24

#define Q_STEP_PIN 36
#define Q_DIR_PIN 34
#define Q_ENABLE_PIN 30



AccelStepper xStepper(1, X_STEP_PIN, X_DIR_PIN); // 1 = Driver
AccelStepper yStepper(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper zStepper(1, Z_STEP_PIN, Z_DIR_PIN);

void setup() {
  Serial.begin(9600);


  yStepper.setMaxSpeed(1000);
  yStepper.setAcceleration(500);
  yStepper.setEnablePin(Y_ENABLE_PIN);
  yStepper.setPinsInverted(false, false, true); //invert logic of enable pin
  yStepper.enableOutputs();
  yStepper.setCurrentPosition(0);

}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    
    if (input.startsWith("s")) {
      yStepper.stop();
      while (yStepper.isRunning()) {
        yStepper.run();
      }
    }
    
    else if (input.toInt() != 0 || input == "0") {
      long target = input.toInt();
      yStepper.moveTo(target);
    }
  }

  yStepper.run();

  // Check if the motor has reached the target position
  if (yStepper.distanceToGo() == 0 && yStepper.currentPosition() == yStepper.targetPosition()) {
    // Print message when the target position is reached
    Serial.println("Target position reached");
  }
}


