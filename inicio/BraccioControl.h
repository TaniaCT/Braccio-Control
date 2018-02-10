#ifndef __BRACCIOCONTROL__
#define __BRACCIOCONTROL__

#include "Modules.h"
#include "Robot.h"
#include "BluetoothModule.h"
#include "EventManager.h"
#include "ProcessDataModule.h"
#include "SerialModule.h"

#define MODULES 5

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
	Robot robot;
	BluetoothModule bt_module;
	EventManager event_manager;
	ProcessDataModule process_data;
	SerialModule serial_mod;
	Module* modules[MODULES];
};

extern BraccioControl braccio;
#endif
