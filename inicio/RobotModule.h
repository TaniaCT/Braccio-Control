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

	// Explicit set of the delay between single movements
	void SetDelay(int step_delay);

	void SetGripper(int gripper_state);

	void JoggingCommand(p2List<int> &list);

	void MoveCommand(p2List<int> &list);

	String BuildStringCurrentAngles();

	void SavePosition(p2List<int> &list);

  void StopProgram();

private:
	RoboticArm arm;
	int positions[NUMBERPOSITIONS*ELEMENTSPOS];
};

#endif 
