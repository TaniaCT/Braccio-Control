#ifndef __SERIALMODULE__
#define __SERIALMODULE__

#include "Modules.h"
#include "Arduino.h"

class SerialModule : public Module
{
public:
	SerialModule();

	void Start();

	void Update();

	void WriteSerial(String data);

private:
	// Enables to get a string of data instead of a single character from the PC console
	String GetLineSerial();

private:
	String received_data = "";
};

#endif
