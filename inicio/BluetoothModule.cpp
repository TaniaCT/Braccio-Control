#include "BluetoothModule.h"

SoftwareSerial BT(4, 2); // RX TX

BluetoothModule::BluetoothModule()
{
}

void BluetoothModule::Start()
{
	Serial.begin(9600);
	BT.begin(9600);
	curr_state = S_DISCONNECTED;
	BT.print("AT");
	time_stamp = millis();
}

void BluetoothModule::Update()
{
	switch (curr_state)
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

	//clean data string
	recieved_data = "";
}

void BluetoothModule::AttemptToConnect()
{
	if (BT.available()) 
	{
		recieved_data = GetLine_BT();
		Serial.println(recieved_data); /// TODO: remove
		if (recieved_data == "OK")
		{ 
			Serial.println("No conectado.");
			BT.print("AT");
			time_stamp = millis();
		}
		else
		{
			curr_state = S_CONNECTED;
		}
	}
	else if (millis() - time_stamp > 1000)
	{
		BT.print("AT");
		time_stamp = millis();
	}
		
}

void BluetoothModule::OnConnection()
{
	if (BT.available())
	{
		recieved_data = GetLine_BT(); 
		Serial.println(recieved_data); /// TODO: remove
		BT.print(recieved_data);

		switch (curr_action)
		{
		case A_NULL:
			break;
		case A_HOPEN:
			break;
		case A_HCLOSE:
			break;
		case A_MOVE_ART:
			break;
		default:
			break;
		}
	}

	if (Serial.available())	/// TODO: remove. Su uso es para configurar el modulo desde consola o enviar ordenes desde consola
	{
		recieved_data = GetLine_Serial();
		BT.print(recieved_data); 
		Serial.print(recieved_data);
	}
}

String BluetoothModule::GetLine_BT()
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
		return (tmp_data);
	}
}

String BluetoothModule::GetLine_Serial() ///TODO: remove
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


