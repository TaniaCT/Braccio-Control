#ifndef __BLUETOOTHMODULE__
#define __BLUETOOTHMODULE__

#include "Modules.h"
#include <SoftwareSerial.h>
#include "Arduino.h"

class BluetoothModule : public Module
{
public:
	enum State {
		S_NULL,
		S_CONNECTED,
		S_DISCONNECTED,
	};

	enum Actions {
		A_NULL,
		A_HOPEN,
		A_HCLOSE,
		A_MOVE_ART
	};

public:
	BluetoothModule();

	void Start();

	void Update();

private:
	void AttemptToConnect();

	void OnConnection();

	String GetLine_BT();

	String GetLine_Serial(); ///TODO: remove

private:
  
	unsigned long time_stamp = 0;
	String recieved_data = "";
	State curr_state = S_NULL;
	Actions curr_action = A_NULL;

	
};
#endif

