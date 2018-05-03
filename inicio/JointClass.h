#ifndef __JOINTCLASS__
#define __JOINTCLASS__

#include <Servo.h>
#include "Arduino.h"

class Joint {

	// Each joint represents a servomotor
	// Each joint of a robot has a minimum angle, a maximum angle and the methods to get them 
	// Each joint of a robot has a current angle, a target angle and the methods to get and set them

public:
	Joint(int min_angle, int max_angle, int current_angle);

	// Function that returns the servo object related to the joint
	Servo GetServo();

	// Function that returns the minimum angle the joint can reach
	int GetMinAngle();

	// Function that returns the minimum angle the joint can reach
	int GetMaxAngle();

	// Function that returns the current angle of the joint
	int GetCurrentAngle();

	// Function that sets the current angle of the joint
	void SetCurrentAngle(int angle);

	// Function that returns the target angle of the joint
	int GetTargetAngle();

	// Function that sets the target angle of the joint
	void SetTargetAngle(int angle);

private:
	// Variables declaration
	Servo servo;
	int min_angle;
	int max_angle;
	int current_angle;
	int target_angle;
};

#endif 

