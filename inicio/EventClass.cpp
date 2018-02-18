#include "EventClass.h"

Event::Event()
{
}

Event::Event(p2List<String> &tokens, EventType type)
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

String Event::GetTokenElement(int position)
{
	return "SEND";//tokens[position];
}
