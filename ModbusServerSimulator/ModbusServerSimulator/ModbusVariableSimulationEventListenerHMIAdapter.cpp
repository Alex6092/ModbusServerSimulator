#include "ModbusVariableSimulationEventListenerHMIAdapter.h"
#include "ModbusServerHMI.h"

using namespace ModbusServerSimulator;

void ModbusVariableSimulationEventListenerHMIAdapter::valueChanged(ModbusVariableSimulation * simulation) {
	hmi->setNeedUpdateHMIFlag();
}
