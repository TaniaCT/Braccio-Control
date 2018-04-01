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

	// Initialitzacion of the Bluetooht module
	void Start();

	// Update of the Bluetooht variables
	//void Update();

	void SendData(String data);

	//int GetBluetoothState();

	void SetBluetoothStateDisconnected();

	// Manages the current state of the connection
	void AttemptToConnect();

	// Process incoming data while the module is connected to a master
	//bool OnConnection();

	// Enables to get a string of data instead of a single character from the module
	String GetData();

	// Enables to get a string of data instead of a single character from the PC console
	//String GetLineSerial(); ///TODO: remove

	// Separates each argument separated by a "separator" and put them in a dinamic list
	//void Tokenize(String tmp_data, p2List<String> &list, char separator);

	//void ProcessData();

private:
	unsigned long time_stamp = 0;
	bool disconnect_checked = false;	
	State curr_state = S_NULL;
	/*Command* jogging;
	Command* disconnect;
	Command* move;
	Command* requestData;
	Command* send;
	Command* commands[N_COMMANDS];*/

};
#endif
