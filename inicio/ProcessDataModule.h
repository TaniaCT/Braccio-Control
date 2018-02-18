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
	// Constructor
	ProcessDataModule();

	void Start();

	void Update();

	// Any communicating module can send received data to be processed
	void ProcessData(String text);

private:
	// Separates each argument separated by a "separator" and put them in a dinamic list
	void Tokenize(String tmp_data, p2List<String> &list, char separator);


private:
	Command* commands[N_COMMANDS];
	Command* disconnect;
	Command* jogging;
	Command* move;
	Command* request_data;
	Command* send;
	Command* program;
};

#endif
