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
	private: System::Windows::Forms::DataGridView^  holdingRegistersData;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Address;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Value;

	private: TcpServer<ModbusParser, ClientState> * server;
	private: ModbusVariableSimulation * simulation;
	private: ModbusVariableSimulationEventListenerHMIAdapter * simuEventListener;
	private: System::Windows::Forms::DataGridView^  coilsData;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridView^  digitalInputData;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn4;
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

				holdingRegistersData->Rows->Clear();
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
			this->holdingRegistersData = (gcnew System::Windows::Forms::DataGridView());
			this->Address = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Value = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->coilsData = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->digitalInputData = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->holdingRegistersData))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->coilsData))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->digitalInputData))->BeginInit();
			this->SuspendLayout();
			// 
			// executeOperationTimer
			// 
			this->executeOperationTimer->Enabled = true;
			this->executeOperationTimer->Interval = 50;
			this->executeOperationTimer->Tick += gcnew System::EventHandler(this, &ModbusServerHMI::executeOperationTimer_Tick);
			// 
			// holdingRegistersData
			// 
			this->holdingRegistersData->AllowUserToAddRows = false;
			this->holdingRegistersData->AllowUserToDeleteRows = false;
			this->holdingRegistersData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->holdingRegistersData->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->Address,
					this->Value
			});
			this->holdingRegistersData->Dock = System::Windows::Forms::DockStyle::Left;
			this->holdingRegistersData->Location = System::Drawing::Point(0, 0);
			this->holdingRegistersData->Name = L"holdingRegistersData";
			this->holdingRegistersData->Size = System::Drawing::Size(277, 488);
			this->holdingRegistersData->TabIndex = 0;
			this->holdingRegistersData->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ModbusServerHMI::wordData_CellEndEdit);
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
			// coilsData
			// 
			this->coilsData->AllowUserToAddRows = false;
			this->coilsData->AllowUserToDeleteRows = false;
			this->coilsData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->coilsData->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2
			});
			this->coilsData->Dock = System::Windows::Forms::DockStyle::Fill;
			this->coilsData->Location = System::Drawing::Point(277, 0);
			this->coilsData->Name = L"coilsData";
			this->coilsData->Size = System::Drawing::Size(618, 488);
			this->coilsData->TabIndex = 1;
			this->coilsData->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ModbusServerHMI::coilsData_CellEndEdit);
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"Address";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"Value";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			// 
			// digitalInputData
			// 
			this->digitalInputData->AllowUserToAddRows = false;
			this->digitalInputData->AllowUserToDeleteRows = false;
			this->digitalInputData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->digitalInputData->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn3,
					this->dataGridViewTextBoxColumn4
			});
			this->digitalInputData->Dock = System::Windows::Forms::DockStyle::Right;
			this->digitalInputData->Location = System::Drawing::Point(584, 0);
			this->digitalInputData->Name = L"digitalInputData";
			this->digitalInputData->Size = System::Drawing::Size(311, 488);
			this->digitalInputData->TabIndex = 2;
			this->digitalInputData->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ModbusServerHMI::digitalInputData_CellEndEdit);
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->HeaderText = L"Address";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->ReadOnly = true;
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->HeaderText = L"Value";
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			// 
			// ModbusServerHMI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(895, 488);
			this->Controls->Add(this->digitalInputData);
			this->Controls->Add(this->coilsData);
			this->Controls->Add(this->holdingRegistersData);
			this->Name = L"ModbusServerHMI";
			this->Text = L"Modbus Server Simulator";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ModbusServerHMI::ModbusServerHMI_Paint);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->holdingRegistersData))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->coilsData))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->digitalInputData))->EndInit();
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
		System::String^ valueStr = holdingRegistersData->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();
		int iVal;
		if (Int32::TryParse(valueStr, iVal))
		{
			System::String^ addressStr = holdingRegistersData->Rows[e->RowIndex]->Cells[0]->Value->ToString();
			int iAddr;
			if (Int32::TryParse(addressStr, iAddr))
			{
				simulation->writeHoldingRegisterValue(iAddr, iVal);
			}
		}
	}

	public: void updateHMI() {
		// Holding registers :
		holdingRegistersData->Rows->Clear();

		const std::map<int, int> & holdingRegistersMemory = simulation->getHoldingRegistersMemory();

		if (holdingRegistersMemory.size() > 0)
		{
			holdingRegistersData->Rows->Add(holdingRegistersMemory.size());

			int row = 0;
			for (auto it = holdingRegistersMemory.cbegin(); it != holdingRegistersMemory.cend(); it++)
			{
				holdingRegistersData->Rows[row]->Cells[0]->Value = (*it).first;
				holdingRegistersData->Rows[row]->Cells[1]->Value = (*it).second;
				row++;
			}
		}

		// Coils :
		coilsData->Rows->Clear();

		const std::map<int, bool> & coilsMemory = simulation->getCoilsMemory();

		if (coilsMemory.size() > 0)
		{
			coilsData->Rows->Add(coilsMemory.size());

			int row = 0;
			for (auto it = coilsMemory.cbegin(); it != coilsMemory.cend(); it++)
			{
				coilsData->Rows[row]->Cells[0]->Value = (*it).first;
				coilsData->Rows[row]->Cells[1]->Value = (*it).second;
				row++;
			}
		}

		digitalInputData->Rows->Clear();

		// Digital inputs :
		const std::map<int, bool> & digitalInputsMemory = simulation->getBinaryInputsMemory();

		if (digitalInputsMemory.size() > 0)
		{
			digitalInputData->Rows->Add(digitalInputsMemory.size());

			int row = 0;
			for (auto it = digitalInputsMemory.cbegin(); it != digitalInputsMemory.cend(); it++)
			{
				digitalInputData->Rows[row]->Cells[0]->Value = (*it).first;
				digitalInputData->Rows[row]->Cells[1]->Value = (*it).second;
				row++;
			}
		}
	}

	private: System::Void coilsData_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		System::String^ valueStr = coilsData->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();
		int iVal;
		if (Int32::TryParse(valueStr, iVal))
		{
			System::String^ addressStr = coilsData->Rows[e->RowIndex]->Cells[0]->Value->ToString();
			int iAddr;
			if (Int32::TryParse(addressStr, iAddr))
			{
				simulation->writeCoilValue(iAddr, iVal);
			}
		}
	}

	private: System::Void digitalInputData_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		System::String^ valueStr = digitalInputData->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();
		int iVal;
		if (Int32::TryParse(valueStr, iVal))
		{
			System::String^ addressStr = digitalInputData->Rows[e->RowIndex]->Cells[0]->Value->ToString();
			int iAddr;
			if (Int32::TryParse(addressStr, iAddr))
			{
				simulation->simulateBinaryInputValue(iAddr, iVal);
			}
		}
	}
};
}
