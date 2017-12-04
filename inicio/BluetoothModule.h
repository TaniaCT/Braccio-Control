#ifndef __BLUETOOTHMODULE__
#define __BLUETOOTHMODULE__

#include "Modules.h"
#include "CommandClass.h"
#include "List.h"
#include <SoftwareSerial.h>
#include "Arduino.h"

#define ARGUMENTS 3
#define N_COMMANDS 4

class BluetoothModule : public Module
{
public:
	enum State {
		S_NULL,
		S_CONNECTED,
		S_DISCONNECTED,
	};

public:
	// Constructor
	BluetoothModule();

	// Initialitzacion of the Bluetooht module
	void Start();

	// Update of the Bluetooht variables
	void Update();

private:
	// Manages the current state of the connection
	void AttemptToConnect();

	// Process incoming data while the module is connected to a master
	void OnConnection();

	// Enables to get a string of data instead of a single character from the module
	String GetLineBT();

	// Enables to get a string of data instead of a single character from the PC console
	String GetLineSerial(); ///TODO: remove

	// Separates each argument separated by a "separator" and put them in a dinamic list
	void Tokenize(p2List<String> &list, char separator);

	void ProcessData();

private:

	unsigned long time_stamp = 0;
	String received_data = "";
	State curr_state = S_NULL;
	Command* jogging;
	Command* disconnect;
	Command* move;
	Command* requestData;
	Command* commands[N_COMMANDS];

};
#endif