#include "EventClass.h"

Event::Event()
{
}

Event::Event(p2List<int> &tokens, EventType type)
{
	this->tokens.Copy(tokens);
	this->type = type;
}

Event::EventType Event::GetEventType()
{
	return type;
}

int Event::GetNumTokens()
{
	return tokens.count();
}

int Event::GetTokenElement(int position)
{
	return 0;//tokens[position];
}
