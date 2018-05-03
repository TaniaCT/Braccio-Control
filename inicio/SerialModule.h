#ifndef __SERIALMODULE__
#define __SERIALMODULE__

#include "Communication.h"
#include "Arduino.h"

class SerialModule : public Communication
{
public:
	// Constructor
	SerialModule() {}

	// Serial initialitzation
	void Start();

	// Implementation of the communication type method SendData, that enables
	// to send especified data to the Serial console
	void SendData(String data);

	// Function that runs while ComsModule Update methode is running
	// and checks if the Serial is enabled. If so, sets the connected state
	void AttemptToConnect();

	// Enables to get a string of data instead of a single character from the Arduino console
	String GetData();
};

#endif
