#include "SerialModule.h"
#include "BraccioControl.h"
#include "ProcessDataModule.h"

SerialModule::SerialModule()
{
}

void SerialModule::Start()
{
	Serial.begin(9600);
	//while (!Serial); 
	///TODO: probar
}

void SerialModule::Update()
{
	if (Serial.available())	/// TODO: remove? Su uso es para configurar el modulo desde consola o enviar ordenes desde consola
	{
		received_data = GetLineSerial();
		Serial.print("Received --> ");
		Serial.println(received_data);

		braccio.process_data.ProcessData(received_data);
	}
}

void SerialModule::WriteSerial(String data)
{
	///TODO
}

String SerialModule::GetLineSerial()
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
}
