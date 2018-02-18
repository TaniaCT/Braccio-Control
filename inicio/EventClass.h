#ifndef __EventClass__
#define __EventClass__

#include "Arduino.h"
#include "List.h"

class Event
{
public:
	enum EventType
	{
		E_NULL,
		E_ROBOT,
		E_CONNECTIVITY,
	};

	Event(); /// Construye un evento a partir de uno que ya existe.
	/// Sirve para que funcione la lista (ADD -> copia el objeto --> primero crea y llena la informacion)
	Event(p2List<String> &tokens, EventType type);

	EventType GetEventType();

	int GetNumTokens();

	String GetTokenElement(int position);

private:
	p2List<String> tokens;
	EventType type = E_NULL;
};

#endif
