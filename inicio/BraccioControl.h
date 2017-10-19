#ifndef __BRACCIOCONTROL__
#define __BRACCIOCONTROL__

#include "Modules.h"
#include "Robot.h"
#include "BluetoothModule.h"

#define MODULES 1

class BraccioControl
{
public:
	// Constructor
	BraccioControl();

	//
	void Start();

	//
	void Update();

	//
	void SetDelay(int step_delay);

public:
	Robot robot;
  BluetoothModule BTMod;
	Module* modules[MODULES];
};

extern BraccioControl braccio;
#endif
