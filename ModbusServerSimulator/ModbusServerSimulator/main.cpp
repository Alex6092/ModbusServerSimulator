
#include "ModbusServerHMI.h"
using namespace ModbusServerSimulator;
using namespace System;
using namespace System::Windows::Forms;

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:main")

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main window and run it
	Application::Run(gcnew ModbusServerHMI());
	return 0;
}