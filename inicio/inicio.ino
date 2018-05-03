#include "BraccioControl.h"

// Initialization of the braccioControl object
BraccioControl braccio;

void setup() 
{
	// Initialization of Braccio object
	braccio.Start();
	Serial.println("End of initialization");
}

void loop() 
{
	// Data update of braccio object
	braccio.Update();
}
