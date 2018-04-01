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

	// Modules initialitzacion
	void Start();

	// Modules update
	void Update();

	// Explicit set of the delay between movements (10 - 30 ms)
	void SetDelay(int step_delay); ///TODO (hacer que sea variable, haciendo las pruebas pertienentes)

public:
	ComsModule coms_module;
	EventManager event_manager;
	ProcessDataModule process_data;
	RobotModule robot;
	
	Module* modules[MODULES];
};

extern BraccioControl braccio;
#endif
