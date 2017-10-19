#include "BraccioControl.h"
#include "RoboticArm.h"

BraccioControl braccio;

void setup() {
	braccio.Start();
  Serial.print("He acabado. \n");
}

void loop() {
	braccio.Update();
}
