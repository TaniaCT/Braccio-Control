#include "BraccioControl.h"

BraccioControl::BraccioControl()
{
	modules[0] = &bt_module;
	modules[1] = &event_manager;
	modules[2] = &robot;
	modules[3] = &process_data;
  modules[4]= &serial_mod;
}

void BraccioControl::Start()
{
	for (int i = 0; i < MODULES; ++i)
		modules[i]->Start();
}

void BraccioControl::Update()
{
	for (int i = 0; i < MODULES; ++i)
		modules[i]->Update();
}

void BraccioControl::SetDelay(int step_delay)
{
	robot.SetDelay(step_delay);
}
