#ifndef __BRACCIOCONTROL__
#define __BRACCIOCONTROL__

#include "Modules.h"
#include "RobotModule.h"
#include "EventManager.h"
#include "ProcessDataModule.h"
#include "ComsModule.h"

#define MODULES 4

class BraccioControl
{
public:
	// Constructor
	BraccioControl();

	// Initialitzacion of Braccio and communications
	void Start();

	// Update of Braccio and communication variables
	void Update();

	// Explicit set of the delay between movements (10 - 30 ms)
	void SetDelay(int step_delay); ///TODO (hacer que sea variable, haciendo las pruebas pertienentes)

public:
	RobotModule robot;
	EventManager event_manager;
	ProcessDataModule process_data;
	ComsModule coms_module;
	Module* modules[MODULES];
};

extern BraccioControl braccio;
#endif
