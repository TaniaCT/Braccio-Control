#ifndef __SERIALMODULE__
#define __SERIALMODULE__

#include "Communication.h"
#include "Arduino.h"

class SerialModule : public Communication
{
public:
	SerialModule();

	void Start();

	//void Update();

	void SendData(String data);

	void AttemptToConnect() {}

	// Enables to get a string of data instead of a single character from the PC console
	String GetData();
};

#endif
