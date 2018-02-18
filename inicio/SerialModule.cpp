#include "SerialModule.h"

SerialModule::SerialModule()
{
	SetName("Serial");
}

void SerialModule::Start()
{
	Serial.begin(9600);
	SetState(S_CONNECTED);
	//while (!Serial); 
	///TODO: probar
}

/*void SerialModule::Update()
{
	if (Serial.available())	/// TODO: remove? Su uso es para configurar el modulo desde consola o enviar ordenes desde consola
	{
		received_data = GetData();

		///TODO: borrar. Es para debug.
		Serial.print("Serial Received --> ");
		Serial.println(received_data);

		braccio.process_data.ProcessData(received_data);
	}
}*/

void SerialModule::SendData(String data)
{
	Serial.println(data);
}

String SerialModule::GetData()
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
	}
	return (tmp_data);
}
