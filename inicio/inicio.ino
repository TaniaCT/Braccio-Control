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
  // put your setup code here, to run once:
  arm.Start();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  arm.SetHand(HAND_CLOSE);
  arm.Move();
  delay(2000);
  arm.SetHand(HAND_OPEN);
  arm.Move();
}
