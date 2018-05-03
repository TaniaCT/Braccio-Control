#ifndef __MODULE__
#define __MODULE__

class Module
{
public:
	// Each module has to have a Start and Update method.

	// Constructor
	Module() {}

	// Module initialization
	virtual void Start() {}

	// Module update
	virtual void Update() {}
};


#endif 

