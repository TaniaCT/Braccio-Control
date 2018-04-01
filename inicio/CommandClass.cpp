#include "CommandClass.h"

Command::Command(int min_args, int max_args, bool immediate, Event::EventType type)
{
	this->min_args = min_args;
	this->max_args = max_args;
	this->immediate = immediate;
	this->type = type;
}

int Command::GetMinArgs() const
{
	return min_args;
}

int Command::GetMaxArgs() const
{
	return max_args;
}

bool Command::GetImmediate() const
{
	return immediate;
}

Event::EventType Command::GetEventType() const
{
	return type;
}