#include "BraccioControl.h"
#include "RoboticArm.h"

BraccioControl braccio;

void setup() 
{
  braccio.Start();
  Serial.print("He acabado. \n");
  /*Serial.begin(9600);
  char* a = new char[5];
  *a = 'e';
  Serial.println(*a);
  delete a;*/
}

void loop() 
{
	braccio.Update();
}
