#ifndef __COMSMODULE__
#define __COMSMODULE__

#include "Modules.h"
#include "Communication.h"
#include "BluetoothModule.h"
#include "SerialModule.h"
#include "EventClass.h"

#define NUM_COMS 2

class ComsModule : public Module
{
public:
	ComsModule();

	void Start();

	void Update();

	void SendData(String data, String _communication);

	void DisconnectComs(String _communication);

	int GetComsState(String _communication);

private:
	Communication* coms[NUM_COMS];
	BluetoothModule bt_module;
	SerialModule serial_module;
};
#endif
