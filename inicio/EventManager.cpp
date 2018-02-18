#include "EventManager.h"

EventManager::EventManager()
{
}

void EventManager::Start()
{
}

void EventManager::Update()
{
}

void EventManager::AddEvent(Event & e)
{
	event_list.add(e);
	///TODO: Probar!!!
	Serial.println(event_list.end->data.GetEventType());
}

bool EventManager::RequestEvent(EventType type, Event &e)
{
	bool ret = false;

	for (p2List_item<Event>* ev = event_list.start; ev != nullptr; ev = ev->next)
	{
		if (ev->data.GetEventType() == type)
		{
			e = ev->data;
			event_list.del(ev);
			ret = true;
			break;
		}
	}

	return ret;
}
