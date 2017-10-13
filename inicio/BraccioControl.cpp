#include "BraccioControl.h"
#include "Arduino.h"

BraccioControl::BraccioControl() 
{
	modules[0] = &robot;
}

void BraccioControl::Start() 
{
  ///Serial.print("He entrado al Braccio Control. \n");
	for (int i= 0; i < MODULES; ++i) 
		modules[i]->Start();
  ///Serial.print("He salido del Braccio Control. \n");
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
