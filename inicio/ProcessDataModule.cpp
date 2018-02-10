#include "ProcessDataModule.h"
#include "BraccioControl.h"
#include "BluetoothModule.h"
#include "Robot.h"
#include "EventManager.h"

ProcessDataModule::ProcessDataModule()
{
	disconnect = new Command("DISCONNECT", 0, 0, true, E_CONNECTIVITY);
	commands[0] = disconnect; 
	jogging = new Command("JOG", 2, 2, true, E_ROBOT);
	commands[1] = jogging;
	move = new Command("MOVE", 2, 12, false, E_ROBOT);
	commands[2] = move;
	request_data = new Command("REQUEST", 0, 0, true, E_CONNECTIVITY); // It always send all the angles when requested
	commands[3] = request_data;
	send = new Command("SEND", 1, 20, true, E_CONNECTIVITY);
	commands[4] = send;
	///TODO
	//Command program("PROGRAM");
}

void ProcessDataModule::Start()
{
}

void ProcessDataModule::Update()
{
}

void ProcessDataModule::ProcessData(String received_data)
{
	p2List<String> tokens;
	Tokenize(received_data, tokens, ' ');

	bool immediate = false;
	bool commandfound = false;
	EventType type = E_NULL;

	for (int i = 0; i < N_COMMANDS; i++)
	{
		if (commands[i]->GetName() == tokens[0])
		{
			int num_args = tokens.count() - 1;
			if (num_args >= commands[i]->GetMinArgs() && num_args <= commands[i]->GetMaxArgs())
			{
				commandfound = true;
				immediate = commands[i]->GetImmediate();
				type = commands[i]->GetEventType();
				break;
			}
		}
	}

	if (commandfound)
	{
		if (immediate)
		{
			switch (type)
			{
			case E_NULL:
				break;
			case E_ROBOT:
				if (tokens[0] == "JOG") braccio.robot.Jogging(tokens);
				break;
			case E_CONNECTIVITY:
				if (tokens[0] == "DISCONNECT") {
					braccio.bt_module.SetBluetoothStateDisconnected();
				}
				else if (tokens[0] == "REQUEST")
				{
					Serial.println(braccio.robot.BuildStringCurrentAngles());
					braccio.bt_module.WriteBluetooth(braccio.robot.BuildStringCurrentAngles());
				}
				else if (tokens[0] == "SEND")
				{
					String tmp_data = "";
					for (p2List_item<String>* item = tokens.start->next; item != nullptr; item = item->next)
					{
						tmp_data += item->data;
						if (item != tokens.end) tmp_data += " ";
					}
					braccio.bt_module.WriteBluetooth(tmp_data);
				}
				break;
			}
		}
		else
		{
			Event e(tokens, type);
			braccio.event_manager.AddEvent(e);
		}
	}
}

void ProcessDataModule::Tokenize(String tmp_data, p2List<String> &list, char separator)
{
	tmp_data += char(-1);
	for (int i = 0; i < tmp_data.length(); i++)
	{
		String tmp = "";
		while (tmp_data.charAt(i) != -1 && tmp_data.charAt(i) != separator && tmp_data.charAt(i) != '\n')
		{
			tmp += tmp_data.charAt(i);
			i++;
		}
		list.add(tmp);
	}
}
