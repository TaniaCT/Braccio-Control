#include "ComsModule.h"
#include "BraccioControl.h"
#include "ProcessDataModule.h"
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
	for (int i = 0; i < NUM_COMS; i++) {
		String received_data = "";
		switch (coms[i]->GetState())
		{
		case Communication::S_NULL: ///TODO: futuramente poner error si procede
			break;
		case Communication::S_CONNECTED:
			received_data = coms[i]->GetData();
			if (received_data != "") {
				Serial.print(coms[i]->GetName());
				Serial.print(" Received --> ");
				Serial.println(received_data);
				braccio.process_data.ProcessData(received_data);
			}
			break;
		case Communication::S_DISCONNECTED:
			coms[i]->AttemptToConnect(); 
			break;
		default:
			break;
		}
	}
}

void ComsModule::SendData(String data, String _communication)
{
	for (int i = 0; i < NUM_COMS; i++)
	{
		if (coms[i]->GetName() == _communication)
		{
			coms[i]->SendData(data);
		}
	}
}

void ComsModule::DisconnectComs(String _communication)
{
	// Serial communication can't be disconnected
	for (int i = 1; i < NUM_COMS; i++)
	{
		if (coms[i]->GetName() == _communication)
		{
			coms[i]->SetState(Communication::S_DISCONNECTED);
		}
	}
}

int ComsModule::GetComsState(String _communication)
{
	Communication::State state = Communication::S_NULL;
	for (int i = 0; i < NUM_COMS; i++)
	{
		if (coms[i]->GetName() == _communication)
		{
			state = coms[i]->GetState();
		}
	}
	return state;
}


