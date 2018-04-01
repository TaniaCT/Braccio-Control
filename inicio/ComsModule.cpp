#include "ComsModule.h"
#include "BraccioControl.h"
#include "ProcessDataModule.h"
#include "EventManager.h"

ComsModule::ComsModule()
{
	coms[0] = &serial_module;
	coms[1] = &bt_module;
}

void ComsModule::Start()
{
	for (int i = 0; i < NUM_COMS; i++) {
		coms[i]->Start();
	}
}

void ComsModule::Update()
{
	//Serial.println("Updating coms module");
	for (int i = 0; i < NUM_COMS; i++) {
		String received_data = "";
		switch (coms[i]->GetState())
		{
		case Communication::S_CONNECTED:
		{
			received_data = coms[i]->GetData();
			if (received_data != "") {
				if (serial_module.GetState() == Communication::S_CONNECTED) {
					Serial.print(i);
					Serial.print(" Received --> ");
					Serial.println(received_data);
				}
				braccio.process_data.ProcessData(received_data);
			}

			/// TODO: Probar el uso de eventos, poco recomendado
			/*if (i == 1) {
				//Serial.println("Requesting from ComsModule 2");
				vent ev;
				if (braccio.event_manager.RequestEvent(Event::E_CONNECTIVITY, ev)) {
					int number_tokens = ev.GetNumTokens();
					Serial.print("Number of tokens: ");
					Serial.println(number_tokens);
					if (number_tokens != 0) {
						Serial.println("Llego aqui"); 
						Serial.println(ev.GetTokenElement(0));
						if (ev.GetTokenElement(0) == 5) // 5 = "SEND"
						{
							String tmp_data = "";
							for (int i = 1; i < number_tokens; i++)
							{
								tmp_data += ev.GetTokenElement(i);
								if (i != number_tokens - 1) tmp_data += " ";
							}
							SendData(tmp_data, "Bluetooth");
						}
					}
				}
			}*/
			break;
		}
		case Communication::S_DISCONNECTED:
			coms[i]->AttemptToConnect(); 
			break;
		case Communication::S_NULL: ///TODO: futuramente poner error si procede
			break;
		default:
			break;
		}
	}
}

void ComsModule::SendData(String data, CommTypes _communication)
{
	// If the communication is connected, then the message can be sent
	if (_communication < CT_NULL && _communication >= 0) {
		if (coms[_communication]->GetState == Communication::S_CONNECTED) coms[_communication]->SendData(data);
	}

	/*switch (_communication)
	{
	case ComsModule::CT_SERIAL:
		coms[0]->SendData(data);
		break;
	case ComsModule::CT_BLUETOOTH:
		coms[1]->SendData(data);
		break;
	case ComsModule::CT_NULL:
		break;
	default:
		break;
	}*/
}

void ComsModule::DisconnectComs(CommTypes _communication)
{
	if (_communication < CT_NULL && _communication >= 0) {
		coms[_communication]->SetState(Communication::S_DISCONNECTED);
		if (_communication == 1) bt_module.SetBluetoothStateDisconnected();
	}
}

void ComsModule::ConnectComs(CommTypes _communication)
{
	if (_communication < CT_NULL && _communication >= 0) {
		coms[_communication]->SetState(Communication::S_CONNECTED);
	}
}

int ComsModule::GetComsState(CommTypes _communication)
{
	Communication::State state = Communication::S_NULL;
	
	if (_communication < CT_NULL && _communication >= 0) {
		state = coms[_communication]->GetState();
	}
	
	return state;
}


