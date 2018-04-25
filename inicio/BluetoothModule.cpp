#include "BluetoothModule.h"

SoftwareSerial BT(4, 2); // RX TX

BluetoothModule::BluetoothModule()
{
}

void BluetoothModule::Start()
{
	//Serial.begin(9600);
	BT.begin(9600);
	SetState(S_DISCONNECTED); ///TODO: crear evento
	BT.print("AT");
	time_stamp = millis();
}

void BluetoothModule::SendData(String data)
{
	Serial.println("To BT -->" + data);
	BT.print(data + "#");
}

void BluetoothModule::SetBluetoothStateDisconnected()
{
	//SetState(S_DISCONNECTED); ///TODO: crear evento
	disconnect_checked = false;
}

void BluetoothModule::AttemptToConnect()
{
	if (BT.available())
	{
		String received_data = GetData();
		if (received_data == "OK" && !disconnect_checked) // Es para que se compruebe solo una vez
		{
			disconnect_checked = true;
			Serial.println(received_data);
			Serial.println("Bluetooth no connected.");
			//BT.print("AT");
			//time_stamp = millis();
		}
		else
		{
			Serial.println("Bluetooth connected.");
			SetState(S_CONNECTED); ///TODO: crear evento
		}
	}
	else if ((millis() - time_stamp > 1000) && !disconnect_checked)
	{
		BT.print("AT");
		time_stamp = millis();
	}
}

String BluetoothModule::GetData()
{
	String tmp_data = "";
	if (BT.available())
	{
		char new_char = BT.read();
		while (new_char != -1)
		{
      if (new_char == '#') break;
			tmp_data += new_char;
			delay(25);
			new_char = BT.read();
		}
	}

	return (tmp_data);
}
