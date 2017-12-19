#include "JointClass.h"

Joint::Joint(String joint_name, int min_angle, int max_angle, int current_angle)
{
	this->joint_name = joint_name;
	this->min_angle = min_angle;
	this->max_angle = max_angle;
	this->current_angle = current_angle;
	target_angle = current_angle;
}

Servo Joint::GetServo()
{
	return servo;
}

String Joint::GetName()
{
	return joint_name;
}

int Joint::GetMinAngle()
{
	return min_angle;
}

int Joint::GetMaxAngle()
{
	return max_angle;
}

int Joint::GetCurrentAngle()
{
	return current_angle;
}

void Joint::SetCurrentAngle(int angle)
{
	current_angle = angle;
}

int Joint::GetTargetAngle()
{
	return target_angle;
}

void Joint::SetTargetAngle(int angle)
{
	target_angle = angle;
}

