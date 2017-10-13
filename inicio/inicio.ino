#include "BraccioControl.h"
#include "RoboticArm.h"

BraccioControl braccio;

void setup() {
  Serial.begin(9600);
	braccio.Start();
  Serial.print("He acabado. \n");
}

void loop() {
	braccio.Update();
  Serial.print("Sigo. \n");
}
