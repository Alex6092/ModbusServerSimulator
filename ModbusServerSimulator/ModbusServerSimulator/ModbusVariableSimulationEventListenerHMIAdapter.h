#pragma once

#include <msclr/gcroot.h>
#include "ModbusVariableSimulationEventListener.h"

namespace ModbusServerSimulator {
	ref class ModbusServerHMI;

	class ModbusVariableSimulationEventListenerHMIAdapter : public ModbusVariableSimulationEventListener
	{
		msclr::gcroot<ModbusServerHMI ^> hmi;

	public:
		ModbusVariableSimulationEventListenerHMIAdapter(ModbusServerHMI ^ toNotify) {
			this->hmi = toNotify;
		}

		~ModbusVariableSimulationEventListenerHMIAdapter() {

		}

		virtual void valueChanged(ModbusVariableSimulation * simulation);
	};
}
