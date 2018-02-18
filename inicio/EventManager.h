#ifndef __EVENTMANAGER__
#define __EVENTMANAGER__

#include "List.h"
#include "Modules.h"
#include "EventClass.h"
#include "Arduino.h"

class EventManager: public Module
{
public:
	EventManager();

	void Start();

	void Update();

	void AddEvent(Event &e);

	bool RequestEvent(Event::EventType type, Event &e);

private:
	p2List<Event> event_list;
};

#endif
