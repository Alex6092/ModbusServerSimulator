#include "ModbusVariableSimulation.h"



ModbusVariableSimulation::ModbusVariableSimulation()
{
}


ModbusVariableSimulation::~ModbusVariableSimulation()
{
}

int ModbusVariableSimulation::readValue(int wordAddress)
{
	bool bWordCreated = false;
	if (memory.find(wordAddress) == memory.end())
		bWordCreated = true;

	int result = memory[wordAddress];

	if (bWordCreated)
		notifyValueChange();

	return result;
}

bool ModbusVariableSimulation::writeValue(int wordAddress, int value)
{
	memory[wordAddress] = value;
	notifyValueChange();
	return true;
}

void ModbusVariableSimulation::notifyValueChange()
{
	for (int i = 0; i < this->eventListeners.size(); i++)
	{
		eventListeners[i]->valueChanged(this);
	}
}