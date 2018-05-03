#include "BluetoothModule.h"

// RX y TX pins will be set at digitals pins 4 and 2
SoftwareSerial BT(4, 2);

BluetoothModule::BluetoothModule()
{
}

void BluetoothModule::Start()
{
	BT.begin(9600);
	SetState(S_DISCONNECTED);

	// At the initialization, AT command is sent in order to check if the Bluetooth module exists
	BT.print("AT");
	time_stamp = millis();
}

void BluetoothModule::SendData(String data)
{
	// The data to be sent will be displayed in the Arduino console
	Serial.println("To BT -->" + data);

	// Uncomment if you need to send AT commands, and comment the other one
	//BT.print(data);

	// Sending of specified data ended with de # char
	BT.print(data + "#");
}

void BluetoothModule::SetBluetoothStateDisconnected()
{
	SetState(S_DISCONNECTED);
	disconnect_checked = false;
}

void BluetoothModule::AttemptToConnect()
{
	// If the reception of data is detected, the data will be managed
	// in order to know the state of the conection
	if (BT.available())
	{
		String received_data = GetData();

		// Checks once if the Bluetooth module exists
		// Checks if the Bluetooth module is actived
		if (received_data == "OK" && !disconnect_checked)
		{
			SetState(S_DISCONNECTED);
			disconnect_checked = true;
			Serial.println(received_data);
			Serial.println("Bluetooth no connected.");
		}
		else
		{
			Serial.println("Bluetooth connected.");
			SetState(S_CONNECTED);
		}
	}

	// If no data has been received, this part checks every second the presence
	// of the Bluetooth module
	else if ((millis() - time_stamp > 1000) && !disconnect_checked)
	{
		BT.print("AT");
		time_stamp = millis();
	}
}

String BluetoothModule::GetData()
{
	String tmp_data = "";

	// If the reception of data is detected, each character will be read and 
	// concatenated until the end of line ( char(-1) or # )
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
