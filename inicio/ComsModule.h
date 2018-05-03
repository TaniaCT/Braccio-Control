#ifndef __COMSMODULE__
#define __COMSMODULE__

#include "Modules.h"
#include "Communication.h"
#include "BluetoothModule.h"
#include "SerialModule.h"

class ComsModule : public Module
{
public:
	// Enumeration that contains the index of the available communication types
	enum CommTypes {
		CT_SERIAL,
		CT_BLUETOOTH,
		CT_NULL
	};
public:
	// Constructor
	ComsModule();

	// Communications initialitzation (Serial, bluetooth)
	void Start();

	// Communications update
	void Update();

	// Function that enables to send any text to any possible communication in connected state
	void SendData(String data, CommTypes _communication);

	// Function that sets the disconnect state to the communication passed as argument
	void DisconnectComs(CommTypes _communication);

	// Function that sets the connect state to the communication passed as argument
	void ConnectComs(CommTypes _communication);

	// Function that returns the current state to the communication passed as argument
	int GetComsState(CommTypes _communication);

private:

	// Variables declaration
	Communication * coms[CT_NULL];
	BluetoothModule bt_module;
	SerialModule serial_module;
};
#endif
