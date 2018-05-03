#include "CommandClass.h"

CommandClass::CommandClass(int min_args, int max_args, CommandClass::AvailableModules type)
{
	// Assignment of the passed variables to the command ones
	this->min_args = min_args;
	this->max_args = max_args;
	this->type = type;
}

int CommandClass::GetMinArgs() const
{
	return min_args;
}

int CommandClass::GetMaxArgs() const
{
	return max_args;
}

CommandClass::AvailableModules CommandClass::GetModuleType() const
{
	return type;
}
