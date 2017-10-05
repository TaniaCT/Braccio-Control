#include "Braccio.h"
#include "RoboticArm.h"

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

RoboticArm arm(20);

void setup() {
  arm.Start();
}

void loop() {
  delay(2000);
  arm.SetGripper(GRIPPER_CLOSE);
  arm.Move();
  delay(2000);
  arm.SetGripper(GRIPPER_OPEN);
  arm.Move();
}
