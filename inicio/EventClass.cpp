#include "EventClass.h"

Event::Event()
{
}

Event::Event(p2List<String> tokens, EventType type)
{
	this->tokens = tokens;
	this->type = type;
}

EventType Event::GetEventType()
{
	return type;
}
