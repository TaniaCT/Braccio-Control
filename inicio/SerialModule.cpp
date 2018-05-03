#include "SerialModule.h"

void SerialModule::Start()
{
	Serial.begin(9600);
	SetState(S_DISCONNECTED);
}

void SerialModule::SendData(String data)
{
	Serial.println(data);
}

void SerialModule::AttemptToConnect()
{
	if (S_DISCONNECTED && Serial) {
		SetState(S_CONNECTED);
		Serial.println("Serial connected");
	}
}

String SerialModule::GetData()
{

	// If the reception of data is detected, each character will be read and 
	// concatenated until the end of line char(-1)
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
	}

	// Also, the acive connection is checked in order to disable sending data through Serial
	// if it's disconnected
	if (S_CONNECTED && !Serial) {
		SetState(S_DISCONNECTED);
	}

	return (tmp_data);
}
