#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::OleDb;

[STAThreadAttribute]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Laba4::MyForm form;
	Application::Run(% form);
}

// функция для проверки на число
bool Check_Number(String^ Text)
{
	bool a = true;
	for (int i = 0; i < Text->Length; i++) {
		if (Text[i] <= 57 && Text[i] >= 48)
		{
		}
		else
		{
			a = false;
		}
	}
	return a;
}
System::Void Laba4::MyForm::button_load_Click(System::Object^ sender, System::EventArgs^ e)
{
	dataGridView_Table->Rows->Clear();

	if (listBox_ChooseTable->SelectedIndex == -1)
	{
		MessageBox::Show("Таблица не выбрана!", "Внимание!");
		return;
	}

	String^ Table_Name = listBox_ChooseTable->SelectedItem->ToString();
	// подключение к БД
	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
	dbConnection->Open();
	// запрос
	String^ query = "SELECT * FROM " + Table_Name;
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbCommand->ExecuteReader();
	if (dbReader->HasRows == false) {
		MessageBox::Show("Таблица пуста!", "Ошибка!");
		dbReader->Close();
		dbConnection->Close();
		return;
	}
	// заполнение таблицы
	if (Table_Name == L"Client")
	{
		dataGridView_Table->ColumnCount = 3;
		dataGridView_Table->Columns[0]->Name = L"Номер клиента";
		dataGridView_Table->Columns[1]->Name = L"Имя";
		dataGridView_Table->Columns[2]->Name = L"Скидка";
		while (dbReader->Read()) {
			dataGridView_Table->Rows->Add(dbReader["Номер клиента"], dbReader["Имя клиента"], dbReader["Скидка клиенту"]);
		}
	}
	else
	{
		dataGridView_Table->ColumnCount = 4;
		dataGridView_Table->Columns[0]->Name = L"Номер заказа";
		dataGridView_Table->Columns[1]->Name = L"Книга";
		dataGridView_Table->Columns[2]->Name = L"Имя клиента";
		dataGridView_Table->Columns[3]->Name = L"Скидка";
		while (dbReader->Read()) {
			dataGridView_Table->Rows->Add(dbReader["Номер заказа"], dbReader["Книга"], dbReader["Имя клиента"], dbReader["Скидка клиенту"]);
		}
	}
	dbReader->Close();
	dbConnection->Close();
}

System::Void Laba4::MyForm::button_add_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView_Table->SelectedRows->Count != 1)
	{
		MessageBox::Show("Выберите одну строку!", "Внимание!");
		return;
	}
	//получаем номер выбранной строки
	int index = dataGridView_Table->SelectedRows[0]->Index;

	for (int i = 0; i < dataGridView_Table->Columns->Count; i++)
	{
		if (dataGridView_Table->Rows[index]->Cells[i]->Value == nullptr)
		{
			MessageBox::Show("Заполните все столбцы!", "Внимание!");
			return;
		}
	}
	// Работа с БД
	if (listBox_ChooseTable->SelectedItem->ToString() == L"Orders")
	{
		// Получем новые данные, вписанный в таблицу
		String^ ID = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		String^ Book = dataGridView_Table->Rows[index]->Cells[1]->Value->ToString();
		String^ Client_Name = dataGridView_Table->Rows[index]->Cells[2]->Value->ToString();
		String^ Client_Discount = dataGridView_Table->Rows[index]->Cells[3]->Value->ToString();
		//Проверяем на корректность числовые значения
		if (!Check_Number(ID) || !Check_Number(Client_Discount))
		{
			MessageBox::Show("Введены некорректные значения номера заказа или скидки клиенту!", "Внимание!");
			return;
		}

		int^ Discount = int::Parse(this->dataGridView_Table->Rows[index]->Cells[3]->Value->ToString());
		if (*Discount > 100)
		{
			MessageBox::Show("Значение скидки не может превышать 100%", "Внимание!");
			return;
		}
		//Подключение к БД
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//Выполнение запроса с добавлением данных в таблицу
		String^ query = "INSERT INTO Orders VALUES(" + ID + ", '" + Book + "', " + Client_Discount + ", '" + Client_Name + "')";
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("Запрос выполнен успешно!", "Внимание!");
			dbConnection->Close();
			return;
		}
	}
	else
	{
		String^ Client_Number = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		String^ Client_Name = dataGridView_Table->Rows[index]->Cells[1]->Value->ToString();
		String^ Client_Discount = dataGridView_Table->Rows[index]->Cells[2]->Value->ToString();
		if (!Check_Number(Client_Discount) || !Check_Number(Client_Number))
		{
			MessageBox::Show("Введены некорректные значения номера или скидки клиенту!", "Внимание!");
			return;
		}

		int^ Discount = int::Parse(this->dataGridView_Table->Rows[index]->Cells[2]->Value->ToString());
		if (*Discount > 100)
		{
			MessageBox::Show("Значение скидки не может превышать 100", "Внимание!");
			return;
		}

		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		String^ query = "INSERT INTO Client VALUES(" + Client_Number + ", '" + Client_Name + "', " + Client_Discount + ")";
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("Запрос выполнен успешно!", "Внимание!");
			dbConnection->Close();
			return;
		}
	}



}

System::Void Laba4::MyForm::button_delete_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView_Table->SelectedRows->Count != 1)
	{
		MessageBox::Show("Выберите одну строку!", "Внимание!");
		return;
	}
	//получаем номер выбранной строки
	int index = dataGridView_Table->SelectedRows[0]->Index;

	if (listBox_ChooseTable->SelectedItem->ToString() == L"Orders")
	{
		String^ ID = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		//Подключение к БД
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//Выполнение запроса на удаление строки
		String^ query = "DELETE FROM Orders WHERE [Номер заказа]=" + ID;
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("Запрос выполнен успешно!", "Внимание!");
			dataGridView_Table->Rows->RemoveAt(index);
			dbConnection->Close();
			return;
		}
	}
	else
	{
		String^ ID = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		//Подключение к БД
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//Выполняем запрос на удаление
		String^ query = "DELETE FROM Client WHERE [Номер клиента]=" + ID;
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("Запрос выполнен успешно!", "Внимание!");
			dataGridView_Table->Rows->RemoveAt(index);
			dbConnection->Close();
			return;
		}
	}

}

System::Void Laba4::MyForm::button_find_number_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ number_str = textBox_number->Text->ToString();
	if (!Check_Number(number_str))
	{
		MessageBox::Show("Введено некорректное значение номера!", "Ошибка!");
		return;
	}
	if (listBox_ChooseTable->SelectedIndex == -1)
	{
		MessageBox::Show("Таблица не выбрана!", "Внимание!");
		return;
	}
	dataGridView_Table->Columns->Clear();
	String^ Table_Name = listBox_ChooseTable->SelectedItem->ToString();
	// подключение к БД
	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
	dbConnection->Open();
	// запрос
	String^ query = "SELECT * FROM " + Table_Name;
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbCommand->ExecuteReader();
	if (dbReader->HasRows == false) {
		MessageBox::Show("Таблица пуста!", "Ошибка!");
		dbReader->Close();
		dbConnection->Close();
		return;
	}
	// заполнение таблицы
	if (Table_Name == L"Client")
	{
		bool a = false;
		dataGridView_Table->ColumnCount = 3;
		dataGridView_Table->Columns[0]->Name = L"Номер клиента";
		dataGridView_Table->Columns[1]->Name = L"Имя";
		dataGridView_Table->Columns[2]->Name = L"Скидка";
		String^ buf = nullptr;
		while (dbReader->Read()) {
			buf = dbReader["Номер клиента"]->ToString();
			if (buf == number_str)
			{
				dataGridView_Table->Rows->Add(dbReader["Номер клиента"], dbReader["Имя клиента"], dbReader["Скидка клиенту"]);
				a = true;
			}
		}
		if (!a)
		{
			MessageBox::Show("Ничего не найдено!", "Внимание!");
		}
	}
	else
	{
		bool a = false;
		dataGridView_Table->ColumnCount = 4;
		dataGridView_Table->Columns[0]->Name = L"Номер заказа";
		dataGridView_Table->Columns[1]->Name = L"Книга";
		dataGridView_Table->Columns[2]->Name = L"Имя клиента";
		dataGridView_Table->Columns[3]->Name = L"Скидка";
		String^ buf = nullptr;
		while (dbReader->Read()) {
			buf = dbReader["Номер заказа"]->ToString();
			if (buf == number_str)
			{
				dataGridView_Table->Rows->Add(dbReader["Номер заказа"], dbReader["Книга"], dbReader["Имя клиента"], dbReader["Скидка клиенту"]);
				a = true;
			}
		}
		if (!a)
		{
			MessageBox::Show("Ничего не найдено!", "Внимание!");
		}
	}
	dbReader->Close();
	dbConnection->Close();
	
}

System::Void Laba4::MyForm::button_find_discount_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ discount_str = textBox_number->Text->ToString();
	if (!Check_Number(discount_str))
	{
		MessageBox::Show("Введено некорректное значение скидки!", "Ошибка!");
		return;
	}
	if (listBox_ChooseTable->SelectedIndex == -1)
	{
		MessageBox::Show("Таблица не выбрана!", "Внимание!");
		return;
	}
	dataGridView_Table->Columns->Clear();
	String^ Table_Name = listBox_ChooseTable->SelectedItem->ToString();
	// подключение к БД
	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
	dbConnection->Open();
	// запрос
	String^ query = "SELECT * FROM " + Table_Name;
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbCommand->ExecuteReader();
	if (dbReader->HasRows == false) {
		MessageBox::Show("Таблица пуста!", "Ошибка!");
		dbReader->Close();
		dbConnection->Close();
		return;
	}
	// заполнение таблицы
	if (Table_Name == L"Client")
	{
		bool a = false;
		dataGridView_Table->ColumnCount = 3;
		dataGridView_Table->Columns[0]->Name = L"Номер клиента";
		dataGridView_Table->Columns[1]->Name = L"Имя";
		dataGridView_Table->Columns[2]->Name = L"Скидка";
		String^ buf = nullptr;
		while (dbReader->Read()) {
			buf = dbReader["Скидка клиенту"]->ToString();
			if (buf == discount_str)
			{
				dataGridView_Table->Rows->Add(dbReader["Номер клиента"], dbReader["Имя клиента"], dbReader["Скидка клиенту"]);
				a = true;
			}
		}
		if (!a)
		{
			MessageBox::Show("Ничего не найдено!", "Внимание!");
		}
	}
	else
	{
		bool a = false;
		dataGridView_Table->ColumnCount = 4;
		dataGridView_Table->Columns[0]->Name = L"Номер заказа";
		dataGridView_Table->Columns[1]->Name = L"Книга";
		dataGridView_Table->Columns[2]->Name = L"Имя клиента";
		dataGridView_Table->Columns[3]->Name = L"Скидка";
		String^ buf = nullptr;
		while (dbReader->Read()) {
			buf = dbReader["Скидка клиенту"]->ToString();
			if (buf == discount_str)
			{
				dataGridView_Table->Rows->Add(dbReader["Номер заказа"], dbReader["Книга"], dbReader["Имя клиента"], dbReader["Скидка клиенту"]);
				a = true;
			}
		}
		if (!a)
		{
			MessageBox::Show("Ничего не найдено!", "Внимание!");
		}
	}
	dbReader->Close();
	dbConnection->Close();

}

System::Void Laba4::MyForm::button_update_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView_Table->SelectedRows->Count != 1)
	{
		MessageBox::Show("Выберите одну строку!", "Внимание!");
		return;
	}
	//получаем номер выбранной строки
	int index = dataGridView_Table->SelectedRows[0]->Index;

	for (int i = 0; i < dataGridView_Table->Columns->Count; i++)
	{
		if (dataGridView_Table->Rows[index]->Cells[i]->Value == nullptr)
		{
			MessageBox::Show("Заполните все столбцы!", "Внимание!");
			return;
		}
	}
	// Работа с БД
	if (listBox_ChooseTable->SelectedItem->ToString() == L"Orders")
	{
		// Получем новые данные, вписанные в таблицу
		String^ ID = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		String^ Book = dataGridView_Table->Rows[index]->Cells[1]->Value->ToString();
		String^ Client_Name = dataGridView_Table->Rows[index]->Cells[2]->Value->ToString();
		String^ Client_Discount = dataGridView_Table->Rows[index]->Cells[3]->Value->ToString();
		//Проверяем на корректность числовые значения
		if (!Check_Number(ID) || !Check_Number(Client_Discount))
		{
			MessageBox::Show("Введены некорректные значения номера заказа или скидки клиенту!", "Внимание!");
			return;
		}

		int^ Discount = int::Parse(this->dataGridView_Table->Rows[index]->Cells[3]->Value->ToString());
		if (*Discount > 100)
		{
			MessageBox::Show("Значение скидки не может превышать 100%", "Внимание!");
			return;
		}
		//Подключение к БД
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//Выполнение запроса на изменение данных в таблице
		String^ query = "UPDATE Orders SET [Книга]='" + Book + "', [Скидка клиенту]=" + Client_Discount + ", [Имя клиента]='" + Client_Name + "' WHERE [Номер заказа]=" + ID;
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("Запрос выполнен успешно!", "Внимание!");
			dbConnection->Close();
			return;
		}
	}
	else
	{
		// Получаем новые данные, вписанные в таблицу
		String^ Client_Number = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		String^ Client_Name = dataGridView_Table->Rows[index]->Cells[1]->Value->ToString();
		String^ Client_Discount = dataGridView_Table->Rows[index]->Cells[2]->Value->ToString();
		// Проверям на корректность числовые значения
		if (!Check_Number(Client_Discount) || !Check_Number(Client_Number))
		{
			MessageBox::Show("Введены некорректные значения номера или скидки клиенту!", "Внимание!");
			return;
		}

		int^ Discount = int::Parse(this->dataGridView_Table->Rows[index]->Cells[2]->Value->ToString());
		if (*Discount > 100)
		{
			MessageBox::Show("Значение скидки не может превышать 100", "Внимание!");
			return;
		}
		//Подключение к БД
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//Выполняем запрос на изменение
		String^ query = "UPDATE Client SET [Имя клиента]='" + Client_Name + "', [Скидка клиенту]=" + Client_Discount + " WHERE [Номер клиента]=" + Client_Number;
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("Ошибка выполнения запроса!", "Ошибка!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("Запрос выполнен успешно!", "Внимание!");
			dbConnection->Close();
			return;
		}
	}
}

System::Void Laba4::MyForm::listBox_ChooseTable_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	dataGridView_Table->Columns->Clear();
	return System::Void();
}