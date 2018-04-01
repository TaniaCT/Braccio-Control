#include "ProcessDataModule.h"
#include "BraccioControl.h"
#include "BluetoothModule.h"
#include "RobotModule.h"
#include "EventManager.h"
#include "EventClass.h"
#include "ComsModule.h"

ProcessDataModule::ProcessDataModule()
{
	connect = new Command(1, 1, true, Event::E_CONNECTIVITY);
	commands[0] = connect;
	disconnect = new Command(1, 1, true, Event::E_CONNECTIVITY);
	commands[1] = disconnect;
	request_data = new Command(1, 1, true, Event::E_CONNECTIVITY); // It always send all the angles when requested
	commands[2] = request_data;
	/*move = new Command(2, 12, false, Event::E_ROBOT);
	commands[5] = move;*/
	send = new Command(1, 1, true, Event::E_CONNECTIVITY);
	commands[3] = send;
	jogging = new Command(2, 2, true, Event::E_ROBOT);
	commands[4] = jogging;
	/*program = new Command(1, 20, true, Event::E_CONNECTIVITY);
	commands[6] = program;*/
}

void ProcessDataModule::Start()
{
}

void ProcessDataModule::Update()
{
	//Serial.println("Updating process data module");
}

void ProcessDataModule::ProcessData(String received_data)
{
	if (received_data.charAt(0) < 48 && received_data.charAt(0) > 57) Serial.println(received_data);
	else {
    int command = received_data.substring(0,1).toInt();

    Serial.print("command: ");
    Serial.println(command);

    if (command >= 0 && command < C_NULL){
      p2List<int> tokens;
      if (command == 3) Tokenize(received_data.substring(0,3), tokens, ' ');
      else Tokenize(received_data, tokens, ' ');

      Serial.print("Tokenized: ");
      Serial.println(tokens.count());

      for (int i = 0; i < tokens.count(); i++){
        Serial.println(tokens[i]);
      }

      bool immediate = false;
      bool commandfound = false;
      Event::EventType type = Event::E_NULL;

      if (command < N_COMMANDS) {
        int num_args = tokens.count() - 1;
        Serial.print("num_args: ");
        Serial.println(num_args);
        if (num_args >= commands[command]->GetMinArgs() && num_args <= commands[command]->GetMaxArgs())
        {
          commandfound = true;
          immediate = commands[command]->GetImmediate();
          type = commands[command]->GetEventType();
        }
      }

      if (commandfound)
    {
      //Event e(tokens, type);
      //braccio.event_manager.AddEvent(e);
      switch (type)
      {
      case Event::E_NULL:
        break;
      case Event::E_ROBOT:
        if (command == C_JOG) braccio.robot.Jogging(tokens);
        break;
      case Event::E_CONNECTIVITY:
        // CONNECT
        if (command == C_CONNECT) {
          //braccio.coms_module.SetState();
          braccio.coms_module.ConnectComs((ComsModule::CommTypes)tokens[1]); /// TODO: probar si vale con los enteros
        }
        // DISCONNECT
        else if (command == C_DISCONNECT) {
          braccio.coms_module.DisconnectComs((ComsModule::CommTypes)tokens[1]);
        }
        else if (command == C_REQUEST)
        {
          Serial.println(braccio.robot.BuildStringCurrentAngles());
          braccio.coms_module.SendData(braccio.robot.BuildStringCurrentAngles(), (ComsModule::CommTypes)tokens[1]);
        }
        else if (command == C_SENDTO) /// TODO: Tener en cuenta todos los tipos de comunicaci�n abiertos. Restriccion: solo un modo a la vez
        {
			braccio.coms_module.SendData(received_data.substring(4), (ComsModule::CommTypes)tokens[1]);
			
        /*String tmp_data = "";
        for (p2List_item<int>* item = tokens.start->next; item != nullptr; item = item->next)
        {
        tmp_data += item->data;
        if (item != tokens.end) tmp_data += " ";
        }
        braccio.coms_module.SendData(tmp_data, tokens[1]);
        }
        break;*/
        }
      }
    }
  }
    }
		/*for (int i = 0; i < N_COMMANDS; i++)
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
		}*/
}

void ProcessDataModule::Tokenize(String tmp_data, p2List<int> &list, char separator)
{
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
   tmp.toCharArray(vector_char,5);
		list.add(atoi(vector_char));
	}
}
