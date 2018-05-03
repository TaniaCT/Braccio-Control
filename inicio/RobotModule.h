#ifndef __ROBOTMODULE__
#define __ROBOTMODULE__

#define NUMBERPOSITIONS 20
#define ELEMENTSPOS 6

#include "Modules.h"
#include "RoboticArm.h"
#include "List.h"
#include "Arduino.h"

class RobotModule : public Module
{
public:
	// Constructor
	RobotModule();

	// Initialitzacion of Braccio
	void Start();

	// Update of Braccio variables
	void Update();

	// Explicit set of the delay between single movements of 1 degree
	void SetDelay(int step_delay);

	// Method that sets the maximum or minimum value to the  gripper target 
	// angle,in order to close or open the gripper, respectively
	void SetGripper(int gripper_state);

	// Method that manages the manual control of Braccio movements
	void JoggingCommand(p2List<int> &list);

	// Method that manages the automatic control of Braccio movements
	void MoveCommand(p2List<int> &list);

	// Method that returns a string with the command "Response" followed by the current 
	// angles of all joints, all separated by an space character
	String BuildStringCurrentAngles();

	// Method that manages what to do with specified joint positions
	void SavePosition(p2List<int> &list);

	// Method that stops the execution of the current automatic movement (program)
	void StopProgram();

private:
	// Variables declaration
	RoboticArm arm;
	int positions[NUMBERPOSITIONS*ELEMENTSPOS];
};

#endif 
