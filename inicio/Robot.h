#ifndef __ROBOT__
#define __ROBOT__

#include "Modules.h"
#include "RoboticArm.h"
#include "List.h"
#include "Arduino.h"

class Robot : public Module
{
public:
	// Constructor
	Robot();

	// Initialitzacion of Braccio
	void Start();

	// Update of Braccio variables
	void Update();

	// Explicit set of the delay between single movements
	void SetDelay(int step_delay);

	void SetGripper(String gripper_state);

	void Jogging(p2List<String> &list);

	void MoveCommand(p2List<String> &list);

	String BuildStringCurrentAngles();

private:
	RoboticArm arm;
};

#endif 