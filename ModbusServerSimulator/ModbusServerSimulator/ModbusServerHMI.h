#pragma once

#include "TcpServer.h"
#include "ModbusParser.h"
#include "ModbusOperation.h"
#include "ModbusVariableSimulationEventListenerHMIAdapter.h"
#include <iostream>

namespace ModbusServerSimulator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de ModbusServerHMI
	/// </summary>
	public ref class ModbusServerHMI : public System::Windows::Forms::Form
	{
	
	private: System::Windows::Forms::Timer^  executeOperationTimer;
	private: System::Windows::Forms::DataGridView^  wordData;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Address;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Value;

	private: TcpServer<ModbusParser, ClientState> * server;
	private: ModbusVariableSimulation * simulation;
	private: ModbusVariableSimulationEventListenerHMIAdapter * simuEventListener;
	private: bool needUpdateHMI;
	public: void setNeedUpdateHMIFlag() { needUpdateHMI = true; }

	public:
		ModbusServerHMI(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//

			try
			{
				needUpdateHMI = false;
				simulation = new ModbusVariableSimulation();
				simuEventListener = new ModbusVariableSimulationEventListenerHMIAdapter(this);
				simulation->addEventListener(simuEventListener);
				server = new TcpServer<ModbusParser, ClientState>(502);

				wordData->Rows->Clear();
			}
			catch (std::exception e)
			{
				delete simulation;
				simulation = NULL;
				server = NULL;
				std::cout << e.what() << std::endl;
			}
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~ModbusServerHMI()
		{
			if (components)
			{
				delete components;
			}

			if(server != NULL)
				delete server;

			if (simulation != NULL)
				delete simulation;
		}

	private: System::ComponentModel::IContainer^  components;
	protected:

	protected:

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->executeOperationTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->wordData = (gcnew System::Windows::Forms::DataGridView());
			this->Address = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Value = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->wordData))->BeginInit();
			this->SuspendLayout();
			// 
			// executeOperationTimer
			// 
			this->executeOperationTimer->Enabled = true;
			this->executeOperationTimer->Interval = 50;
			this->executeOperationTimer->Tick += gcnew System::EventHandler(this, &ModbusServerHMI::executeOperationTimer_Tick);
			// 
			// wordData
			// 
			this->wordData->AllowUserToAddRows = false;
			this->wordData->AllowUserToDeleteRows = false;
			this->wordData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->wordData->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->Address, this->Value });
			this->wordData->Dock = System::Windows::Forms::DockStyle::Fill;
			this->wordData->Location = System::Drawing::Point(0, 0);
			this->wordData->Name = L"wordData";
			this->wordData->Size = System::Drawing::Size(609, 305);
			this->wordData->TabIndex = 0;
			this->wordData->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ModbusServerHMI::wordData_CellEndEdit);
			// 
			// Address
			// 
			this->Address->HeaderText = L"Address";
			this->Address->Name = L"Address";
			this->Address->ReadOnly = true;
			// 
			// Value
			// 
			this->Value->HeaderText = L"Value";
			this->Value->Name = L"Value";
			// 
			// ModbusServerHMI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(609, 305);
			this->Controls->Add(this->wordData);
			this->Name = L"ModbusServerHMI";
			this->Text = L"Modbus Server Simulator";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ModbusServerHMI::ModbusServerHMI_Paint);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->wordData))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void executeOperationWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		
	}
	private: System::Void ModbusServerHMI_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		
	}
	private: System::Void executeOperationTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		ModbusParser * parser = this->server->getParser();

		if (needUpdateHMI)
		{
			updateHMI();
			needUpdateHMI = false;
		}

		try
		{
			ThreadSafeQueue<ModbusOperation*> & operations = parser->getOperation();

			while (operations.Size() > 0)
			{
				ModbusOperation * operation = operations.Get();
				operation->Execute(simulation);
				delete operation;
			}
		}
		catch (std::exception e)
		{
			// Quand tu dis merde aux erreurs :P 
		}
	}
	private: System::Void wordData_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		System::String^ valueStr = wordData->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();
		int iVal;
		if (Int32::TryParse(valueStr, iVal))
		{
			System::String^ addressStr = wordData->Rows[e->RowIndex]->Cells[0]->Value->ToString();
			int iAddr;
			if (Int32::TryParse(addressStr, iAddr))
			{
				simulation->writeValue(iAddr, iVal);
			}
		}
	}

	public: void updateHMI() {
		wordData->Rows->Clear();

		const std::map<int, int> & memory = simulation->getMemory();

		wordData->Rows->Add(memory.size());

		int row = 0;
		for (auto it = memory.cbegin(); it != memory.cend(); it++)
		{
			wordData->Rows[row]->Cells[0]->Value = (*it).first;
			wordData->Rows[row]->Cells[1]->Value = (*it).second;
			row++;
		}
	}

};
}
