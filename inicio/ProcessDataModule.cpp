#include "ProcessDataModule.h"
#include "BraccioControl.h"
#include "BluetoothModule.h"
#include "RobotModule.h"
#include "ComsModule.h"

ProcessDataModule::ProcessDataModule()
{
	// Initialization of all available commands
	connect = new CommandClass(1, 1, CommandClass::AvailableModules::M_CONNECTIVITY);
	commands[0] = connect;
	disconnect = new CommandClass(1, 1, CommandClass::AvailableModules::M_CONNECTIVITY);
	commands[1] = disconnect;
	request_data = new CommandClass(1, 1, CommandClass::AvailableModules::M_CONNECTIVITY);
	commands[2] = request_data;
	send = new CommandClass(1, 1, CommandClass::AvailableModules::M_CONNECTIVITY);
	commands[3] = send;
	jogging = new CommandClass(2, 2, CommandClass::AvailableModules::M_ROBOT);
	commands[4] = jogging;
	move = new CommandClass(1, 2, CommandClass::AvailableModules::M_ROBOT);
	commands[5] = move;
	hand = new CommandClass(1, 1, CommandClass::AvailableModules::M_ROBOT);
	commands[6] = hand;
	save_pos = new CommandClass(1, 8, CommandClass::AvailableModules::M_ROBOT);
	commands[7] = save_pos;
	program_stop = new CommandClass(0, 0, CommandClass::AvailableModules::M_ROBOT);
	commands[8] = program_stop;
}

void ProcessDataModule::ProcessData(String received_data)
{
	// If the first character is not number, it will be shown in the Arduino console
	if (received_data.charAt(0) < 48 && received_data.charAt(0) > 57) Serial.println(received_data);

	// If it is, the received data will be processed
	else {
		// Gets de command index
		int command = received_data.substring(0, 1).toInt();

		// Uncomment for debugging purpose

		/*Serial.print("command: ");
		Serial.println(command);*/

		// If the command index is valid, the received data will be tokenized (separated and put into an integer
		// array) and the arguments will be checked since we have maximum and minimum number of arguments that
		// has to have
		if (command >= 0 && command < C_NULL) {
			p2List<int> tokens;
			if (command == 3) Tokenize(received_data.substring(0, 3), tokens, ' ');
			else Tokenize(received_data, tokens, ' ');

			// Uncomment for debugging purpose

			/*for (int i = 0; i < tokens.count(); i++) {
				Serial.println(tokens[i]);
			}*/

			bool commandfound = false;
			CommandClass::AvailableModules type = CommandClass::AvailableModules::M_NULL;
			int num_args = tokens.count() - 1;

			// Uncomment for debugging purpose

			/*Serial.print("num_args: ");
			Serial.println(num_args);*/

			if (num_args >= commands[command]->GetMinArgs() && num_args <= commands[command]->GetMaxArgs())
			{
				commandfound = true;
				type = commands[command]->GetModuleType();
			}

			// If the command syntax is correct, the only thing to do is sending the order to the 
			// module which handles it
			if (commandfound)
			{
				switch (type)
				{
				case CommandClass::AvailableModules::M_NULL:
					break;
				case CommandClass::AvailableModules::M_ROBOT:
					if (command == C_JOGGING) braccio.robot.JoggingCommand(tokens);
					else if (command == C_MOVE) braccio.robot.MoveCommand(tokens);
					else if (command == C_HAND) braccio.robot.SetGripper(tokens[1]);
					else if (command == C_SAVEPOS) braccio.robot.SavePosition(tokens);
					else if (command == C_STOP) braccio.robot.StopProgram();
					break;
				case CommandClass::AvailableModules::M_CONNECTIVITY:
					if (command == C_CONNECT) {
						braccio.coms_module.ConnectComs((ComsModule::CommTypes)tokens[1]);
					}
					else if (command == C_DISCONNECT) {
						braccio.coms_module.DisconnectComs((ComsModule::CommTypes)tokens[1]);
					}
					else if (command == C_REQUEST) {
						braccio.coms_module.SendData(braccio.robot.BuildStringCurrentAngles(), (ComsModule::CommTypes)tokens[1]);
					}
					else if (command == C_SENDTO) {
						braccio.coms_module.SendData(received_data.substring(4), (ComsModule::CommTypes)tokens[1]);
					}
				}
			}
		}
	}
}

void ProcessDataModule::Tokenize(String tmp_data, p2List<int> &list, char separator)
{
	// Each character is concatenated and checked until it's equal to the separator character, end of line or a line break
	// This Tokenize method is exclusive for the creation of integers lists
	tmp_data += char(-1);
	for (int i = 0; i < tmp_data.length(); i++)
	{
		String tmp = "";
		char tmp_char = tmp_data.charAt(i);
		while (tmp_char != -1 && tmp_char != separator && tmp_char != '\n')
		{
			tmp += tmp_char;
			i++;
			tmp_char = tmp_data.charAt(i);
		}
		char vector_char[5];
		tmp.toCharArray(vector_char, 5);
		list.add(atoi(vector_char));
	}
}
