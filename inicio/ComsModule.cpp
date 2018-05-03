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
	// For each available communication type, a Start() method will be called
	for (int i = 0; i < CT_NULL; i++) {
		coms[i]->Start();
	}
}

void ComsModule::Update()
{
	// According to the current state of each communication type, if they are disabled, an 
	// attempToConnect method will verify if it's activated again. Otherwise, if the current
	// state is connected, the reception of data from them will be monirtorized.
	// When some data is received, it goes to the ProcessDataModule in order to be processed.
	for (int i = 0; i < CT_NULL; i++) {
		String received_data = "";

		switch (coms[i]->GetState())
		{

		case Communication::S_CONNECTED:
		{
			received_data = coms[i]->GetData();
			if (received_data != "") {
				if (serial_module.GetState() == Communication::S_CONNECTED) {

					// Uncomment in case of need some debbuging at this part

					/*Serial.print(i);
					Serial.print(" Received --> ");
					Serial.println(received_data);*/
				}
				braccio.process_data.ProcessData(received_data);
			}
			break;
		}
		case Communication::S_DISCONNECTED:
			coms[i]->AttemptToConnect();
			break;
		case Communication::S_NULL:
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
		if (GetComsState(_communication) == Communication::S_CONNECTED)
			coms[_communication]->SendData(data);
	}
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


