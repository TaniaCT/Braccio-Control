#ifndef __COMMUNICATION__
#define __COMMUNICATION__

#include "Arduino.h"

class Communication
{

	// Each communication type has a curr_state variable and a Start, SendData, 
	// AttempToConnect and GetData methods. Also, the curr_state can be set and get.

public:
	enum State {
		S_CONNECTED,
		S_DISCONNECTED,
		S_NULL
	};

public:
	// Constructor
	Communication() {}

	// Communication type initialization
	virtual void Start() {}

	// Method that allows to send specified data through the communication type
	virtual void SendData(String data) {}

	// Method that checks if the communication type becomes actived.
	virtual void AttemptToConnect() {}

	// Method that checks the reception of data
	virtual String GetData() { return ""; }

	// Function that returns the current state to the communication type
	State GetState() { return curr_state; }

	// Function that sets the current state to the communication type
	void SetState(State state) { curr_state = state; }

private:
	// Variables declaration
	State curr_state = S_NULL;
};

#endif
