#ifndef __COMMANDCLASS__
#define __COMMANDCLASS__

class CommandClass
{
	// Each command class has a managing module related to the command behaviour,
	// a number of minimum arguments, a number of maximum arguments and the methods
	// to get them

public:
	enum AvailableModules {
		M_CONNECTIVITY,
		M_ROBOT,
		M_NULL
	};

public:
	// Constructor
	CommandClass(int min_args, int max_args, AvailableModules type);

	// Method that returns the minimun arguments related to the command behaviour
	int GetMinArgs() const;

	// Method that returns the maximum arguments related to the command behaviour
	int GetMaxArgs() const;

	// Method that returns the managing module related to the command behaviour
	AvailableModules GetModuleType() const;

private:
	// Variables declaration
	int min_args;
	int max_args;
	AvailableModules type;
};

#endif
