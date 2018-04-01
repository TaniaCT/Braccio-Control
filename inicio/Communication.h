#ifndef __COMMUNICATION__
#define __COMMUNICATION__

#include "Arduino.h"

class Communication
{
public:
	enum State {
		S_CONNECTED,
		S_DISCONNECTED,
		S_NULL
	};

public:
	Communication() {}

	virtual void Start() {}

	virtual void SendData(String data) {}

	virtual void AttemptToConnect() {}

	virtual String GetData() { return ""; }

	//String GetName() { return name; }

	//void SetName(String name) { if(this->name == "") this->name = name; }

	State GetState() { return curr_state; }

	void SetState(State state) { curr_state = state; }

private:
	//String name = "";
	State curr_state = S_NULL;
};

#endif
