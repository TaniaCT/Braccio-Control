#ifndef __BLUETOOTHMODULE__
#define __BLUETOOTHMODULE__

#include "Communication.h"
#include <SoftwareSerial.h>
#include "Arduino.h"

class BluetoothModule : public Communication
{

public:
	// Constructor
	BluetoothModule();

	// Initialitzacion of the Bluetooth module
	void Start();

	// Implementation of the communication type method SendData, that enables
	// to send especified data through the Bluetooth module
	void SendData(String data);

	// Method that sets the Bluetooth current state to disconnected
	void SetBluetoothStateDisconnected();

	// Manages the current state of the connection
	void AttemptToConnect();

	// Enables to get a string of data instead of a single character from the module
	String GetData();


private:

	// Variables declaration
	unsigned long time_stamp = 0;
	bool disconnect_checked = false;
	State curr_state = S_NULL;

};
#endif
