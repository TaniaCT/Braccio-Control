#ifndef __ROBOTICARM__
#define __ROBOTICARM__

#include <Servo.h>
#include "Arduino.h"
#include "JointClass.h"

class RoboticArm
{
public:
	// Constructor. Needs to set a delay in ms between 10 and 30.
	RoboticArm(int step_delay = 20);

	// Initialize Braccio to default position
	void Start(bool soft_start = true);

	// Perform Braccio simple movements
	void Move();

	// Sets the state of the gripper: GRIPPER_OPEN, GRIPPER_CLOSE
	void SetGripper(String gripper_state);

	// Sets a new delay between single movements from 10 up to 30.
	void SetDelay(int step_delay);

	// Sets the target angle of a determinate joint ("Base", "Shoulder", 
	//"Elbow", "Wrist_ver", "Wrist_rot", "Gripper")
	// If the angle is not inside the range of the joint, the limit values
	// will be set.
	void SetJointAngles(String servo_name, int angle);

	int GetCurrentAngles(String servo_name);

private:
	// This function, used only with the Braccio Shield V4 and greater,
	// turn ON the Braccio softly and save Braccio from brokes.
	// The SOFT_START_CONTROL_PIN is used as a software PWM
	// @param soft_start_level: the minimum value is -70, default: 0
	void SoftStart(int soft_start_level);

	// Software implementation of the PWM for the SOFT_START_CONTROL_PIN, HIGH
	// @param high_time: the time in the logic level high
	// @param low_time : the time in the logic level low
	void SoftwarePWM(int high_time, int low_time);

private:

	int step_delay;
 bool moving = false;
 bool send_message = false;

	Joint* base;
	Joint* shoulder;
	Joint* elbow;
	Joint* wrist_ver;
	Joint* wrist_rot;
	Joint* gripper;
	Joint* joints[6];
};

#endif
