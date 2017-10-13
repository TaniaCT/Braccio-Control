#ifndef __ROBOT__
#define __ROBOT__

#include "Modules.h"
#include "RoboticArm.h"

class Robot : public Module
{
public:
	Robot();

	void Start();

	void Update();

	void SetDelay(int step_delay);

private:
	RoboticArm arm;
};

#endif 

