#ifndef __BRACCIOCONTROL__
#define __BRACCIOCONTROL__

#include "Modules.h"
#include "RobotModule.h"
#include "ProcessDataModule.h"
#include "ComsModule.h"

#define MODULES 3

class BraccioControl
{
public:
	// Constructor
	BraccioControl();

	// Modules initialization
	void Start();

	// Modules update
	void Update();

	// Explicit set of the minimum delay between movements of 1 degree (10 - 30 ms)
	void SetDelay(int step_delay);

public:
	// Variabless declaration
	ComsModule coms_module;
	ProcessDataModule process_data;
	RobotModule robot;

	Module* modules[MODULES];
};

extern BraccioControl braccio;
#endif
