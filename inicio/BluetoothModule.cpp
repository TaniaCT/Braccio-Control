#include "BluetoothModule.h"

SoftwareSerial BT(4, 2); // RX TX

BluetoothModule::BluetoothModule()
{
	SetName("Bluetooth");
	/*jogging = new Command("JOG", 2, 2, true, E_ROBOT);
	commands[0] = jogging;
	disconnect = new Command("DISCONNECT", 0, 0, true, E_CONNECTIVITY);
	commands[1] = disconnect;
	move = new Command("MOVE", 2, 12, false, E_ROBOT);
	commands[2] = move;
	requestData = new Command("REQUEST", 0, 0, true, E_CONNECTIVITY); //It always send all the angles when requested
	commands[3] = requestData;
	send = new Command("SEND", 1, 20, true, E_CONNECTIVITY);
	commands[4] = send;
	///TODO
	//Command program("PROGRAM");*/ 
}

void BluetoothModule::Start()
{
	//Serial.begin(9600);
	BT.begin(9600);
	SetState(S_DISCONNECTED);
	BT.print("AT");
	time_stamp = millis();
}

/*void BluetoothModule::Update()
{
	/*switch (curr_state)
	{
	case S_NULL: ///TODO: futuramente poner error si procede
		break;
	case S_CONNECTED:
		OnConnection();
		break;
	case S_DISCONNECTED:
		AttemptToConnect();
		break;
	default:
		break;
	}

	// Clean data string, after each update
	received_data = "";
}*/

void BluetoothModule::SendData(String data)
{
	Serial.println("To BT -->" + data);
	BT.print(data + "#");
}

/*int BluetoothModule::GetBluetoothState()
{
	return curr_state;
}*/

void BluetoothModule::SetBluetoothStateDisconnected()
{
	SetState(S_DISCONNECTED);
	disconnect_checked = false;
}

void BluetoothModule::AttemptToConnect()
{
	if (BT.available())
	{
		String received_data = GetData();
		if (received_data == "OK" && !disconnect_checked) ///TODO: para que lo compruebe solo una vez
		{
			disconnect_checked = true;
			Serial.println(received_data);
			Serial.println("Unconnected.");
			//BT.print("AT");
			//time_stamp = millis();
		}
		else
		{
			Serial.println("Connected.");
			SetState(S_CONNECTED);
		}
	}
	else if ((millis() - time_stamp > 1000) && !disconnect_checked)
	{
		BT.print("AT");
		time_stamp = millis();
	}
}

/*String BluetoothModule::OnConnection()
{
	if (BT.available())
	{
		received_data = GetData();
		Serial.print("Received --> ");
		Serial.println(received_data);	/// TODO: remove. 
		//BT.print(received_data+"#");		/// Esta es la confirmacion de lo que se ha recibido

		//braccio.process_data.ProcessData(received_data);
	}

	if (Serial.available())	/// TODO: remove? Su uso es para configurar el modulo desde consola o enviar ordenes desde consola
	{
		received_data = GetLineSerial();
		Serial.print("Received --> ");
		Serial.println(received_data);

		ProcessData();
	}
	return recieved_data;
}*/

String BluetoothModule::GetData()
{
	String tmp_data = "";
	if (BT.available())
	{
		char new_char = BT.read();
		while (new_char != -1)
		{
			tmp_data += new_char;
			delay(25);
			new_char = BT.read();
		}
	}

	return (tmp_data);
}

/*String BluetoothModule::GetLineSerial() ///TODO: remove
{
	String tmp_data = "";
	if (Serial.available())
	{
		char new_char = Serial.read();
		while (new_char != -1)
		{
			tmp_data += new_char;
			delay(25);
			new_char = Serial.read();
		}
		return (tmp_data);
	}
}*/

/*void BluetoothModule::Tokenize(String tmp_data, p2List<String> &list, char separator)
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
}*/

/*void BluetoothModule::ProcessData()
{
	p2List<String> tokens;
	Tokenize(received_data, tokens, ' ');

	bool immediate = false;
	bool found = false;
	EventType type = E_NULL;

	for (int i = 0; i < N_COMMANDS; i++)
	{
		if (commands[i]->GetName() == tokens[0])
		{
			int num_args = tokens.count() - 1;
			if (num_args >= commands[i]->GetMinArgs() && num_args <= commands[i]->GetMaxArgs())
			{
				found = true;
				immediate = commands[i]->GetImmediate();
				type = commands[i]->GetEventType();
				break;
			}
		}
	}

	if (found)
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
					curr_state = S_DISCONNECTED;
					disconnect_checked = false;
				}
				else if (tokens[0] == "REQUEST")
				{
					Serial.println(braccio.robot.BuildStringCurrentAngles());
					WriteBluetooth(braccio.robot.BuildStringCurrentAngles());
				}
				else if (tokens[0] == "SEND")
				{
				String tmp_data = "";
					for (p2List_item<String>* item = tokens.start->next; item != nullptr; item = item->next)
					{
						tmp_data += item->data;
						if (item != tokens.end) tmp_data += " ";
					}
				WriteBluetooth(tmp_data);
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
}*/
