#ifndef __ROBOTICARM__
#define __ROBOTICARM__

#include "Braccio.h"
#include <Servo.h>

// Gripper possible states
enum GripperState
{
  GRIPPER_NULL,										/// Se pone por seguridad
  GRIPPER_OPEN,
  GRIPPER_CLOSE
};

class RoboticArm
{
public:
	// Constructor. Need to set a delay in ms. Between 10 and 30.
	RoboticArm(int step_delay);

	// Initialize Braccio to default position
	void Start();

	// Perform Braccio simple movements
	void Move();

	// Sets the state of the gripper: GRIPPER_OPEN, GRIPPER_CLOSE
	void SetGripper(GripperState state);

private:

	_Braccio braccio;

	int step_delay;
	int m1 = 0;
	int m2 = 45;
	int m3 = 180;
	int m4 = 180;
	int m5 = 90;
	int m6 = 10;  
  
};
#endif
