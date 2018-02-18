#include "BraccioControl.h"

BraccioControl::BraccioControl()
{
	modules[0] = &coms_module;
	modules[1] = &event_manager;
	modules[2] = &process_data;
	modules[3] = &robot;
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
