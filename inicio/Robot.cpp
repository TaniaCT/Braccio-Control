#include "Robot.h"
#include "Arduino.h"

Robot::Robot()
{
}

void Robot::Start()
{
  ///Serial.print("He entrado al Robot. \n");
	///arm.Start();

  arm.SetGripper(GRIPPER_CLOSE);
  ///Serial.print("He salido del Robot. \n");
}

void Robot::Update()
{
	arm.Move();
}

void Robot::SetDelay(int step_delay)
{
	arm.SetDelay(step_delay);
}
