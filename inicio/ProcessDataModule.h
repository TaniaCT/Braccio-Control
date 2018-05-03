#ifndef __PROCESSDATAMODULE__
#define __PROCESSDATAMODULE__

#include "Modules.h"
#include "CommandClass.h"
#include "List.h"
#include "Arduino.h"

#define N_COMMANDS 9

class ProcessDataModule : public Module
{
public:

	// Enumeration that contains the index of the available command types
	enum CommandTypes {
		C_CONNECT,
		C_DISCONNECT,
		C_REQUEST,
		C_SENDTO,
		C_JOGGING,
		C_MOVE,
		C_HAND,
		C_SAVEPOS,
		C_STOP,
		C_NULL
	};
public:
	// Constructor
	ProcessDataModule();

	// Start and Update methods are declared, for future usages 
	void Start() {}
	void Update() {}

	// Any communicating module can send received data to be processed
	// in this method
	void ProcessData(String text);

private:
	// Separates each argument separated by a "separator" and put them in a dinamic list
	void Tokenize(String tmp_data, p2List<int> &list, char separator);


private:
	// Variables declaration
	CommandClass * commands[N_COMMANDS];
	CommandClass* connect;
	CommandClass* disconnect;
	CommandClass* request_data;
	CommandClass* send;
	CommandClass* jogging;
	CommandClass* move;
	CommandClass* hand;
	CommandClass* save_pos;
	CommandClass* program_stop;
};

#endif
