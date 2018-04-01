#include "EventManager.h"
#include "Arduino.h"
//#include "ComsModule.h" ///TODO: quitar

EventManager::EventManager()
{
}

void EventManager::Start()
{
}

void EventManager::Update()
{
	//Serial.println("Updating event manager");
}

void EventManager::AddEvent(Event & e)
{
	event_list.add(e);
	///TODO: Probar!!!
	//if (serial_module.GetState() == Communication::S_CONNECTED) {
		Serial.print("Nuevo evento añadido --> Tipo: ");
		Serial.println(event_list.end->data.GetEventType());
	//}
}

bool EventManager::RequestEvent(Event::EventType type, Event &e)
{
	Serial.print("Requested event --> Tipo: ");
	Serial.println(type);
	bool ret = false;
	if (type != Event::E_NULL) {
		for (p2List_item<Event>* ev = event_list.start; ev != nullptr; ev = ev->next)
		{
			if (ev->data.GetEventType() == type)
			{
				e = ev->data;
				Serial.print("Found event type: ");
				Serial.println(e.GetEventType());
				event_list.del(ev);
				Serial.println("cosas no varias");
				ret = true;
				break;
			}
		}
	}

	return ret;
}
