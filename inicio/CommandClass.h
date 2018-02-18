#ifndef __COMMANDCLASS__
#define __COMMANDCLASS__

#include "EventManager.h"
#include "EventClass.h"

class Command
{
public:
	Command(String name, int min_args, int max_args, bool immediate, Event::EventType type);

	String GetName() const;

	int GetMinArgs() const;

	int GetMaxArgs() const;

	bool GetImmediate() const;

	Event::EventType GetEventType() const;

private:
	String name;
	int min_args;
	int max_args;
	bool immediate;
	Event::EventType type;
};

#endif
