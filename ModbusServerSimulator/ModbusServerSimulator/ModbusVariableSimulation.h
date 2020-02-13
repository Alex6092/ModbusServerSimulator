#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include "ModbusVariableSimulationEventListener.h"

class ModbusVariableSimulation
{
	std::map<int, bool> coilsMemory;
	std::map<int, bool> binaryInputsMemory;
	std::map<int, int> holdingRegistersmemory;
	std::vector<ModbusVariableSimulationEventListener *> eventListeners;


	void notifyValueChange();
public:
	ModbusVariableSimulation();
	~ModbusVariableSimulation();

	// Coils:
	bool readCoilValue(int coilAddress);
	bool writeCoilValue(int coilAddress, bool value);

	// Inputs :
	bool readBinaryInputValue(int inputAddress);
	bool simulateBinaryInputValue(int inputAddress, bool value);

	// Holding registers :
	int readHoldingRegisterValue(int wordAddress);
	bool writeHoldingRegisterValue(int wordAddress, int value);

	inline const std::map<int, int> & getHoldingRegistersMemory() { return holdingRegistersmemory; }

	inline const std::map<int, bool> & getCoilsMemory() { return coilsMemory; }

	inline const std::map<int, bool> & getBinaryInputsMemory() { return binaryInputsMemory; }

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

