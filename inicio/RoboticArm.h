#ifndef __ROBOTICARM__
#define __ROBOTICARM__

#include <Servo.h>

// Gripper possible states
enum GripperState
{
  GRIPPER_NULL,										/// Se pone por seguridad
  GRIPPER_OPEN,
  GRIPPER_CLOSE
};

enum Servos
{
	S_BASE,
	S_SHOULDER,
	S_ELBOW,
	S_WRIST_VER,
	S_WRIST_ROT
};

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
	void SetGripper(GripperState state);

	// Sets a new delay between single movements from 10 up to 30.
	void SetDelay(int step_delay);

	// Sets...
	void SetAngles(Servos servos, int angle);

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
	Servo base;
	Servo shoulder;
	Servo elbow; 
	Servo wrist_ver; 
	Servo wrist_rot; 
	Servo gripper; 

	int step_delay;

	//current angles = default values
	int base_angle = 0;
	int shoulder_angle = 45;
	int elbow_angle = 180;
	int wrist_ver_angle = 180;
	int wrist_rot_angle = 90;
	int gripper_angle = 10;

	//target angles = default values
	int target_base_angle = 0;
	int target_shoulder_angle = 45;
	int target_elbow_angle = 180;
	int target_wrist_ver_angle = 180;
	int target_wrist_rot_angle = 90;
	int target_gripper_angle = 10;
};
#endif
