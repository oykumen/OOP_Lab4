#pragma once

namespace Laba4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ listBox_ChooseTable;
	private: System::Windows::Forms::DataGridView^ dataGridView_Table;
	protected:

	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ button_find_discount;
	private: System::Windows::Forms::Button^ button_find_number;
	private: System::Windows::Forms::TextBox^ textBox_number;
	private: System::Windows::Forms::Button^ button_delete;
	private: System::Windows::Forms::Button^ button_add;
	private: System::Windows::Forms::Button^ button_update;
	private: System::Windows::Forms::Button^ button_load;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listBox_ChooseTable = (gcnew System::Windows::Forms::ListBox());
			this->dataGridView_Table = (gcnew System::Windows::Forms::DataGridView());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button_find_discount = (gcnew System::Windows::Forms::Button());
			this->button_find_number = (gcnew System::Windows::Forms::Button());
			this->textBox_number = (gcnew System::Windows::Forms::TextBox());
			this->button_delete = (gcnew System::Windows::Forms::Button());
			this->button_add = (gcnew System::Windows::Forms::Button());
			this->button_update = (gcnew System::Windows::Forms::Button());
			this->button_load = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_Table))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// listBox_ChooseTable
			// 
			this->listBox_ChooseTable->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listBox_ChooseTable->FormattingEnabled = true;
			this->listBox_ChooseTable->ItemHeight = 22;
			this->listBox_ChooseTable->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Client", L"Orders" });
			this->listBox_ChooseTable->Location = System::Drawing::Point(425, 306);
			this->listBox_ChooseTable->Name = L"listBox_ChooseTable";
			this->listBox_ChooseTable->Size = System::Drawing::Size(109, 70);
			this->listBox_ChooseTable->TabIndex = 0;
			this->listBox_ChooseTable->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox_ChooseTable_SelectedIndexChanged);
			// 
			// dataGridView_Table
			// 
			this->dataGridView_Table->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_Table->Location = System::Drawing::Point(12, 12);
			this->dataGridView_Table->Name = L"dataGridView_Table";
			this->dataGridView_Table->RowHeadersWidth = 51;
			this->dataGridView_Table->RowTemplate->Height = 24;
			this->dataGridView_Table->Size = System::Drawing::Size(522, 288);
			this->dataGridView_Table->TabIndex = 1;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button_find_discount);
			this->groupBox1->Controls->Add(this->button_find_number);
			this->groupBox1->Controls->Add(this->textBox_number);
			this->groupBox1->Controls->Add(this->button_delete);
			this->groupBox1->Controls->Add(this->button_add);
			this->groupBox1->Controls->Add(this->button_update);
			this->groupBox1->Controls->Add(this->button_load);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.2F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(543, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(195, 364);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Действия";
			// 
			// button_find_discount
			// 
			this->button_find_discount->Location = System::Drawing::Point(6, 276);
			this->button_find_discount->Name = L"button_find_discount";
			this->button_find_discount->Size = System::Drawing::Size(183, 37);
			this->button_find_discount->TabIndex = 6;
			this->button_find_discount->Text = L"Поиск по скидке";
			this->button_find_discount->UseVisualStyleBackColor = true;
			this->button_find_discount->Click += gcnew System::EventHandler(this, &MyForm::button_find_discount_Click);
			// 
			// button_find_number
			// 
			this->button_find_number->Location = System::Drawing::Point(6, 233);
			this->button_find_number->Name = L"button_find_number";
			this->button_find_number->Size = System::Drawing::Size(183, 37);
			this->button_find_number->TabIndex = 5;
			this->button_find_number->Text = L"Поиск по номеру";
			this->button_find_number->UseVisualStyleBackColor = true;
			this->button_find_number->Click += gcnew System::EventHandler(this, &MyForm::button_find_number_Click);
			// 
			// textBox_number
			// 
			this->textBox_number->Location = System::Drawing::Point(6, 205);
			this->textBox_number->Name = L"textBox_number";
			this->textBox_number->Size = System::Drawing::Size(183, 27);
			this->textBox_number->TabIndex = 4;
			// 
			// button_delete
			// 
			this->button_delete->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_delete->Location = System::Drawing::Point(6, 162);
			this->button_delete->Name = L"button_delete";
			this->button_delete->Size = System::Drawing::Size(183, 37);
			this->button_delete->TabIndex = 3;
			this->button_delete->Text = L"Удалить";
			this->button_delete->UseVisualStyleBackColor = true;
			this->button_delete->Click += gcnew System::EventHandler(this, &MyForm::button_delete_Click);
			// 
			// button_add
			// 
			this->button_add->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button_add->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_add->Location = System::Drawing::Point(6, 76);
			this->button_add->Name = L"button_add";
			this->button_add->Size = System::Drawing::Size(183, 37);
			this->button_add->TabIndex = 2;
			this->button_add->Text = L"Добавить";
			this->button_add->UseVisualStyleBackColor = true;
			this->button_add->Click += gcnew System::EventHandler(this, &MyForm::button_add_Click);
			// 
			// button_update
			// 
			this->button_update->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_update->Location = System::Drawing::Point(6, 119);
			this->button_update->Name = L"button_update";
			this->button_update->Size = System::Drawing::Size(183, 37);
			this->button_update->TabIndex = 1;
			this->button_update->Text = L"Обновить";
			this->button_update->UseVisualStyleBackColor = true;
			this->button_update->Click += gcnew System::EventHandler(this, &MyForm::button_update_Click);
			// 
			// button_load
			// 
			this->button_load->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_load->Location = System::Drawing::Point(6, 33);
			this->button_load->Name = L"button_load";
			this->button_load->Size = System::Drawing::Size(183, 37);
			this->button_load->TabIndex = 0;
			this->button_load->Text = L"Загрузить";
			this->button_load->UseVisualStyleBackColor = true;
			this->button_load->Click += gcnew System::EventHandler(this, &MyForm::button_load_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(742, 388);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->listBox_ChooseTable);
			this->Controls->Add(this->dataGridView_Table);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(760, 435);
			this->MinimumSize = System::Drawing::Size(760, 435);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Table";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_Table))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_load_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_add_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_update_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_delete_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_find_number_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_find_discount_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void listBox_ChooseTable_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
};
}
