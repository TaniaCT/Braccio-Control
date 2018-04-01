#ifndef __PROCESSDATAMODULE__
#define __PROCESSDATAMODULE__

#include "Modules.h"
#include "CommandClass.h"
#include "List.h"
#include "Arduino.h"

#define N_COMMANDS 6

class ProcessDataModule : public Module
{
public:
	enum CommandTypes {
		C_CONNECT,
		C_DISCONNECT,
		C_REQUEST,
		C_SENDTO,
		C_JOG,
		C_NULL
	};
public:
	// Constructor
	ProcessDataModule();

	void Start();

	void Update();

	// Any communicating module can send received data to be processed
	void ProcessData(String text);

private:
	// Separates each argument separated by a "separator" and put them in a dinamic list
	void Tokenize(String tmp_data, p2List<int> &list, char separator);


private:
	Command* commands[N_COMMANDS];
	Command* connect;
	Command* disconnect;
	Command* request_data;
	Command* send;
	Command* jogging;
	//Command* move;
	//Command* program;
};

#endif
