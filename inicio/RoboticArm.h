#ifndef __ROBOTICARM__
#define __ROBOTICARM__

#include <Servo.h>
#include "Arduino.h"
#include "JointClass.h"

class RoboticArm
{
public:

	// Enumeration that contains the index of the available joint types
	enum JointTypes {
		JT_BASE,
		JT_SHOULDER,
		JT_ELBOW,
		JT_WRIST_VER,
		JT_WRIST_ROT,
		JT_GRIPPER,
		JT_NULL
	};
public:
	// Constructor. Needs to set a delay in ms between 10 and 30.
	RoboticArm(int step_delay = 20);

	// Initialize Braccio to default position
	void Start(bool soft_start = true);

	// Perform Braccio 1 degree movements until it reached the target angles
	void Move();

	// Sets a new delay between single movements from 10 up to 30.
	void SetDelay(int step_delay);

	// Sets the target angle of a determinate joint type ("Base", "Shoulder", 
	//"Elbow", "Wrist_ver", "Wrist_rot", "Gripper")
	void SetJointAngles(JointTypes joint_type, int angle);

	// Method that returns the current angle of an specified joint
	int GetCurrentAngles(JointTypes joint_type);

private:
	// This function, used only with the Braccio Shield V4 and greater,
	// turn ON the Braccio softly and save Braccio from brokes.
	// The SOFT_START_CONTROL_PIN is used as a software PWM
	// @param soft_start_level: the minimum value is -70, default: 0
	void SoftStart(int soft_start_level);

	// Software implementation of the PWM for the SOFT_START_CONTROL_PIN, HIGH
	void SoftwarePWM(int high_time, int low_time);

private:
	// Variables initialization
	int step_delay;
	bool moving = false;
	bool send_message = false;

	Joint* base;
	Joint* shoulder;
	Joint* elbow;
	Joint* wrist_ver;
	Joint* wrist_rot;
	Joint* gripper;
	Joint* joints[JT_NULL];
};

#endif
