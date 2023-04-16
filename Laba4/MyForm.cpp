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

// ������� ��� �������� �� �����
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
		MessageBox::Show("������� �� �������!", "��������!");
		return;
	}

	String^ Table_Name = listBox_ChooseTable->SelectedItem->ToString();
	// ����������� � ��
	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
	dbConnection->Open();
	// ������
	String^ query = "SELECT * FROM " + Table_Name;
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbCommand->ExecuteReader();
	if (dbReader->HasRows == false) {
		MessageBox::Show("������� �����!", "������!");
		dbReader->Close();
		dbConnection->Close();
		return;
	}
	// ���������� �������
	if (Table_Name == L"Client")
	{
		dataGridView_Table->ColumnCount = 3;
		dataGridView_Table->Columns[0]->Name = L"����� �������";
		dataGridView_Table->Columns[1]->Name = L"���";
		dataGridView_Table->Columns[2]->Name = L"������";
		while (dbReader->Read()) {
			dataGridView_Table->Rows->Add(dbReader["����� �������"], dbReader["��� �������"], dbReader["������ �������"]);
		}
	}
	else
	{
		dataGridView_Table->ColumnCount = 4;
		dataGridView_Table->Columns[0]->Name = L"����� ������";
		dataGridView_Table->Columns[1]->Name = L"�����";
		dataGridView_Table->Columns[2]->Name = L"��� �������";
		dataGridView_Table->Columns[3]->Name = L"������";
		while (dbReader->Read()) {
			dataGridView_Table->Rows->Add(dbReader["����� ������"], dbReader["�����"], dbReader["��� �������"], dbReader["������ �������"]);
		}
	}
	dbReader->Close();
	dbConnection->Close();
}

System::Void Laba4::MyForm::button_add_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView_Table->SelectedRows->Count != 1)
	{
		MessageBox::Show("�������� ���� ������!", "��������!");
		return;
	}
	//�������� ����� ��������� ������
	int index = dataGridView_Table->SelectedRows[0]->Index;

	for (int i = 0; i < dataGridView_Table->Columns->Count; i++)
	{
		if (dataGridView_Table->Rows[index]->Cells[i]->Value == nullptr)
		{
			MessageBox::Show("��������� ��� �������!", "��������!");
			return;
		}
	}
	// ������ � ��
	if (listBox_ChooseTable->SelectedItem->ToString() == L"Orders")
	{
		// ������� ����� ������, ��������� � �������
		String^ ID = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		String^ Book = dataGridView_Table->Rows[index]->Cells[1]->Value->ToString();
		String^ Client_Name = dataGridView_Table->Rows[index]->Cells[2]->Value->ToString();
		String^ Client_Discount = dataGridView_Table->Rows[index]->Cells[3]->Value->ToString();
		//��������� �� ������������ �������� ��������
		if (!Check_Number(ID) || !Check_Number(Client_Discount))
		{
			MessageBox::Show("������� ������������ �������� ������ ������ ��� ������ �������!", "��������!");
			return;
		}

		int^ Discount = int::Parse(this->dataGridView_Table->Rows[index]->Cells[3]->Value->ToString());
		if (*Discount > 100)
		{
			MessageBox::Show("�������� ������ �� ����� ��������� 100%", "��������!");
			return;
		}
		//����������� � ��
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//���������� ������� � ����������� ������ � �������
		String^ query = "INSERT INTO Orders VALUES(" + ID + ", '" + Book + "', " + Client_Discount + ", '" + Client_Name + "')";
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("������ ���������� �������!", "������!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("������ �������� �������!", "��������!");
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
			MessageBox::Show("������� ������������ �������� ������ ��� ������ �������!", "��������!");
			return;
		}

		int^ Discount = int::Parse(this->dataGridView_Table->Rows[index]->Cells[2]->Value->ToString());
		if (*Discount > 100)
		{
			MessageBox::Show("�������� ������ �� ����� ��������� 100", "��������!");
			return;
		}

		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		String^ query = "INSERT INTO Client VALUES(" + Client_Number + ", '" + Client_Name + "', " + Client_Discount + ")";
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("������ ���������� �������!", "������!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("������ �������� �������!", "��������!");
			dbConnection->Close();
			return;
		}
	}



}

System::Void Laba4::MyForm::button_delete_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView_Table->SelectedRows->Count != 1)
	{
		MessageBox::Show("�������� ���� ������!", "��������!");
		return;
	}
	//�������� ����� ��������� ������
	int index = dataGridView_Table->SelectedRows[0]->Index;

	if (listBox_ChooseTable->SelectedItem->ToString() == L"Orders")
	{
		String^ ID = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		//����������� � ��
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//���������� ������� �� �������� ������
		String^ query = "DELETE FROM Orders WHERE [����� ������]=" + ID;
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("������ ���������� �������!", "������!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("������ �������� �������!", "��������!");
			dataGridView_Table->Rows->RemoveAt(index);
			dbConnection->Close();
			return;
		}
	}
	else
	{
		String^ ID = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		//����������� � ��
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//��������� ������ �� ��������
		String^ query = "DELETE FROM Client WHERE [����� �������]=" + ID;
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("������ ���������� �������!", "������!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("������ �������� �������!", "��������!");
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
		MessageBox::Show("������� ������������ �������� ������!", "������!");
		return;
	}
	if (listBox_ChooseTable->SelectedIndex == -1)
	{
		MessageBox::Show("������� �� �������!", "��������!");
		return;
	}
	dataGridView_Table->Columns->Clear();
	String^ Table_Name = listBox_ChooseTable->SelectedItem->ToString();
	// ����������� � ��
	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
	dbConnection->Open();
	// ������
	String^ query = "SELECT * FROM " + Table_Name;
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbCommand->ExecuteReader();
	if (dbReader->HasRows == false) {
		MessageBox::Show("������� �����!", "������!");
		dbReader->Close();
		dbConnection->Close();
		return;
	}
	// ���������� �������
	if (Table_Name == L"Client")
	{
		bool a = false;
		dataGridView_Table->ColumnCount = 3;
		dataGridView_Table->Columns[0]->Name = L"����� �������";
		dataGridView_Table->Columns[1]->Name = L"���";
		dataGridView_Table->Columns[2]->Name = L"������";
		String^ buf = nullptr;
		while (dbReader->Read()) {
			buf = dbReader["����� �������"]->ToString();
			if (buf == number_str)
			{
				dataGridView_Table->Rows->Add(dbReader["����� �������"], dbReader["��� �������"], dbReader["������ �������"]);
				a = true;
			}
		}
		if (!a)
		{
			MessageBox::Show("������ �� �������!", "��������!");
		}
	}
	else
	{
		bool a = false;
		dataGridView_Table->ColumnCount = 4;
		dataGridView_Table->Columns[0]->Name = L"����� ������";
		dataGridView_Table->Columns[1]->Name = L"�����";
		dataGridView_Table->Columns[2]->Name = L"��� �������";
		dataGridView_Table->Columns[3]->Name = L"������";
		String^ buf = nullptr;
		while (dbReader->Read()) {
			buf = dbReader["����� ������"]->ToString();
			if (buf == number_str)
			{
				dataGridView_Table->Rows->Add(dbReader["����� ������"], dbReader["�����"], dbReader["��� �������"], dbReader["������ �������"]);
				a = true;
			}
		}
		if (!a)
		{
			MessageBox::Show("������ �� �������!", "��������!");
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
		MessageBox::Show("������� ������������ �������� ������!", "������!");
		return;
	}
	if (listBox_ChooseTable->SelectedIndex == -1)
	{
		MessageBox::Show("������� �� �������!", "��������!");
		return;
	}
	dataGridView_Table->Columns->Clear();
	String^ Table_Name = listBox_ChooseTable->SelectedItem->ToString();
	// ����������� � ��
	String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
	dbConnection->Open();
	// ������
	String^ query = "SELECT * FROM " + Table_Name;
	OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbCommand->ExecuteReader();
	if (dbReader->HasRows == false) {
		MessageBox::Show("������� �����!", "������!");
		dbReader->Close();
		dbConnection->Close();
		return;
	}
	// ���������� �������
	if (Table_Name == L"Client")
	{
		bool a = false;
		dataGridView_Table->ColumnCount = 3;
		dataGridView_Table->Columns[0]->Name = L"����� �������";
		dataGridView_Table->Columns[1]->Name = L"���";
		dataGridView_Table->Columns[2]->Name = L"������";
		String^ buf = nullptr;
		while (dbReader->Read()) {
			buf = dbReader["������ �������"]->ToString();
			if (buf == discount_str)
			{
				dataGridView_Table->Rows->Add(dbReader["����� �������"], dbReader["��� �������"], dbReader["������ �������"]);
				a = true;
			}
		}
		if (!a)
		{
			MessageBox::Show("������ �� �������!", "��������!");
		}
	}
	else
	{
		bool a = false;
		dataGridView_Table->ColumnCount = 4;
		dataGridView_Table->Columns[0]->Name = L"����� ������";
		dataGridView_Table->Columns[1]->Name = L"�����";
		dataGridView_Table->Columns[2]->Name = L"��� �������";
		dataGridView_Table->Columns[3]->Name = L"������";
		String^ buf = nullptr;
		while (dbReader->Read()) {
			buf = dbReader["������ �������"]->ToString();
			if (buf == discount_str)
			{
				dataGridView_Table->Rows->Add(dbReader["����� ������"], dbReader["�����"], dbReader["��� �������"], dbReader["������ �������"]);
				a = true;
			}
		}
		if (!a)
		{
			MessageBox::Show("������ �� �������!", "��������!");
		}
	}
	dbReader->Close();
	dbConnection->Close();

}

System::Void Laba4::MyForm::button_update_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (dataGridView_Table->SelectedRows->Count != 1)
	{
		MessageBox::Show("�������� ���� ������!", "��������!");
		return;
	}
	//�������� ����� ��������� ������
	int index = dataGridView_Table->SelectedRows[0]->Index;

	for (int i = 0; i < dataGridView_Table->Columns->Count; i++)
	{
		if (dataGridView_Table->Rows[index]->Cells[i]->Value == nullptr)
		{
			MessageBox::Show("��������� ��� �������!", "��������!");
			return;
		}
	}
	// ������ � ��
	if (listBox_ChooseTable->SelectedItem->ToString() == L"Orders")
	{
		// ������� ����� ������, ��������� � �������
		String^ ID = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		String^ Book = dataGridView_Table->Rows[index]->Cells[1]->Value->ToString();
		String^ Client_Name = dataGridView_Table->Rows[index]->Cells[2]->Value->ToString();
		String^ Client_Discount = dataGridView_Table->Rows[index]->Cells[3]->Value->ToString();
		//��������� �� ������������ �������� ��������
		if (!Check_Number(ID) || !Check_Number(Client_Discount))
		{
			MessageBox::Show("������� ������������ �������� ������ ������ ��� ������ �������!", "��������!");
			return;
		}

		int^ Discount = int::Parse(this->dataGridView_Table->Rows[index]->Cells[3]->Value->ToString());
		if (*Discount > 100)
		{
			MessageBox::Show("�������� ������ �� ����� ��������� 100%", "��������!");
			return;
		}
		//����������� � ��
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//���������� ������� �� ��������� ������ � �������
		String^ query = "UPDATE Orders SET [�����]='" + Book + "', [������ �������]=" + Client_Discount + ", [��� �������]='" + Client_Name + "' WHERE [����� ������]=" + ID;
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("������ ���������� �������!", "������!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("������ �������� �������!", "��������!");
			dbConnection->Close();
			return;
		}
	}
	else
	{
		// �������� ����� ������, ��������� � �������
		String^ Client_Number = dataGridView_Table->Rows[index]->Cells[0]->Value->ToString();
		String^ Client_Name = dataGridView_Table->Rows[index]->Cells[1]->Value->ToString();
		String^ Client_Discount = dataGridView_Table->Rows[index]->Cells[2]->Value->ToString();
		// �������� �� ������������ �������� ��������
		if (!Check_Number(Client_Discount) || !Check_Number(Client_Number))
		{
			MessageBox::Show("������� ������������ �������� ������ ��� ������ �������!", "��������!");
			return;
		}

		int^ Discount = int::Parse(this->dataGridView_Table->Rows[index]->Cells[2]->Value->ToString());
		if (*Discount > 100)
		{
			MessageBox::Show("�������� ������ �� ����� ��������� 100", "��������!");
			return;
		}
		//����������� � ��
		String^ connectionString = "provider=Microsoft.Jet.OLEDB.4.0;Data Source=Laba.mdb";
		OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);
		dbConnection->Open();
		//��������� ������ �� ���������
		String^ query = "UPDATE Client SET [��� �������]='" + Client_Name + "', [������ �������]=" + Client_Discount + " WHERE [����� �������]=" + Client_Number;
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConnection);

		if (dbCommand->ExecuteNonQuery() != 1)
		{
			MessageBox::Show("������ ���������� �������!", "������!");
			dbConnection->Close();
			return;
		}
		else
		{
			MessageBox::Show("������ �������� �������!", "��������!");
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