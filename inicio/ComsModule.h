#ifndef __COMSMODULE__
#define __COMSMODULE__

#include "Modules.h"
#include "Communication.h"
#include "BluetoothModule.h"
#include "SerialModule.h"
#include "EventClass.h"

//#define NUM_COMS 2

class ComsModule : public Module
{
public:
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

	// Function that set the disconnect state to the communication passed
	void DisconnectComs(CommTypes _communication);

	// Function that set the connect state to the communication passed
	void ConnectComs(CommTypes _communication);

	// Function that get the state to the communication passed
	int GetComsState(CommTypes _communication);

private:
	Communication* coms[CT_NULL];
	BluetoothModule bt_module;
	SerialModule serial_module;
};
#endif
