#include "Robot.h"

Robot::Robot()
{
}

void Robot::Start()
{
	arm.Start();
}

void Robot::Update()
{
	arm.Move();
}

void Robot::SetDelay(int step_delay)
{
	arm.SetDelay(step_delay);
}

void Robot::SetGripper(String gripper_state)
{
	if (gripper_state == "hopen" || gripper_state == "hclose") arm.SetGripper(gripper_state);
}

void Robot::Jogging(p2List<String> &list)
{
	// From the mobile, you will send +1/0/-1, which means that joint will move towards
	// the maximum or minimum angle or will remain where it is
	if(list[2] == "+1") {
	  arm.SetJointAngles(list[1], 180);
	}
	else if (list[2] == "-1") arm.SetJointAngles(list[1], 0);
	else if (list[2] == "0")
	{
		int curr_angle = arm.GetCurrentAngles(list[1]);
		if (curr_angle != -1) arm.SetJointAngles(list[1], curr_angle);
	}
}

void Robot::MoveCommand(p2List<String>& list)
{
	for (int i = 1; i < list.count(); i + 2)
	{
		arm.SetJointAngles(list[i], atoi(list[i+1].c_str()));
	}
}

String Robot::GetCurrentAngles()
{
	String angles = "RESPONSE ";
	angles.concat(String(arm.GetCurrentAngles("Base")));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles("Shoulder")));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles("Elbow")));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles("Wrist_ver")));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles("Wrist_rot")));
	angles.concat(" ");
	angles.concat(String(arm.GetCurrentAngles("Gripper")));

	return angles;
}
