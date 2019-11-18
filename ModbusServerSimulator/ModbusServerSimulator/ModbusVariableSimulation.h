#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include "ModbusVariableSimulationEventListener.h"

class ModbusVariableSimulation
{
	std::map<int, int> memory;
	std::vector<ModbusVariableSimulationEventListener *> eventListeners;


	void notifyValueChange();
public:
	ModbusVariableSimulation();
	~ModbusVariableSimulation();

	int readValue(int wordAddress);
	bool writeValue(int wordAddress, int value);

	inline const std::map<int, int> & getMemory() { return memory; }

	inline void addEventListener(ModbusVariableSimulationEventListener * listener)
	{
		eventListeners.push_back(listener);
	}

	inline void removeEventListener(ModbusVariableSimulationEventListener * listener)
	{
		auto it = std::find(eventListeners.begin(), eventListeners.end(), listener);
		if (it != eventListeners.end())
		{
			eventListeners.erase(it);
		}
	}
};

