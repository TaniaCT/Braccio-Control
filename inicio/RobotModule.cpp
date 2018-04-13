#include "RobotModule.h"

RobotModule::RobotModule()
{
}

void RobotModule::Start()
{
	arm.Start();
}

void RobotModule::Update()
{
	//Serial.println("Updating robot module");
	arm.Move();
}

void RobotModule::SetDelay(int step_delay)
{
	arm.SetDelay(step_delay);
}

void RobotModule::SetGripper(int gripper_state)
{
  Serial.println(gripper_state);
	if (gripper_state == 0) arm.SetJointAngles(RoboticArm::JointTypes::JT_GRIPPER, 10);
	else if (gripper_state == 1) arm.SetJointAngles(RoboticArm::JointTypes::JT_GRIPPER, 73);
}

void RobotModule::JoggingCommand(p2List<int> &list)
{
	// From the mobile, you will send 1/0/2, which means that joint will move towards
	// the maximum or minimum angle or will remain where it is
	if(list[2] == 2) {
	  arm.SetJointAngles((RoboticArm::JointTypes)list[1], 180);
	}
	else if (list[2] == 1) arm.SetJointAngles((RoboticArm::JointTypes)list[1], 0);
	else if (list[2] == 0)
	{
		int curr_angle = arm.GetCurrentAngles((RoboticArm::JointTypes)list[1]);
		if (curr_angle != -1) arm.SetJointAngles((RoboticArm::JointTypes)list[1], curr_angle);
	}
}

void RobotModule::MoveCommand(p2List<int>& list)
{
	if (list[1] >= 0 && list[1] <= 5) arm.SetJointAngles((RoboticArm::JointTypes)list[1], list[2]);
	//else if (list[1] >= 6 && list[1] <= 8) // Set de los XYZ
	//else //Mirar posiciones disponibles
}

String RobotModule::BuildStringCurrentAngles()
{
	String angles = "RESPONSE ";
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_BASE)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_SHOULDER)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_ELBOW)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_WRIST_VER)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_WRIST_ROT)));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles(RoboticArm::JointTypes::JT_GRIPPER)));

	return angles;
}
