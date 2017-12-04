#ifndef __COMMANDCLASS__
#define __COMMANDCLASS__

#include "EventManager.h"

class Command
{
public:
	Command(String name, int min_args, int max_args, bool immediate, EventType type);

	String GetName() const;

	int GetMinArgs() const;

	int GetMaxArgs() const;

	bool GetImmediate() const;

	EventType GetEventType() const;

private:
	String name;
	int min_args;
	int max_args;
	bool immediate;
	EventType type;
};

#endif
