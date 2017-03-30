
#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

#include "SupportFunc.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

using namespace std;


int selector()
{
 	int result;
 	while (true)
 	{
 		cin >> result;
 		if (cin.fail() == true)
 		{
 			cin.clear();
 			cin.ignore(numeric_limits<std::streamsize>::is_integer, '\n');
 			continue;
 		}

 		cin.ignore(numeric_limits<std::streamsize>::is_integer, '\n');
 		return result;
 	}
}

struct DataStruct
{
	int Id;
 	string Product_name; // название товара
	string Category; // категория
	int Price; //цена
	string Description ; // описание товара

};

vector<DataStruct> Storage;

void WriteLine()
{
	cout << "________________________________________________________________________________" << endl;
}

DataStruct UiData()
{
	DataStruct NewData;


	cout << "Название товара :";
	getline(cin, NewData.Product_name);
	
	cout << "Категория товара :";
	getline(cin, NewData.Category);
	
	cout << "Цена: " << endl;
	NewData.Price = selector();
	
	cout << "Описание товара:";
	getline(cin, NewData.Description);

	return NewData;

}

DataStruct AddData()
{
	WriteLine();

	cout << "Добавление данных" << endl;

	DataStruct NewData = UiData();

	cout << "Данные добавлены " << endl;
	WriteLine();
	return NewData;

}

DataStruct EditStorage()
{
	WriteLine();
	cout << "Изменение данных" << endl;

	DataStruct NewData;
	NewData = UiData();

	cout << "Данные Изменены " << endl;
	WriteLine();
	return NewData;
}

void LoadFile()
{
	ifstream file;
	file.open("Backup.buc");
	if (file.is_open() == false)
	{
		cout << "Файл не может быть открыт " << endl;
		return;
	}
	int CountData = 0;
	string buf;
	string line;
	file >> CountData;

	DataStruct tmp;
	
	Storage.clear();
	while (!file.eof())
	{

		getline(file, buf);
		if (buf == "{")
		{
		    getline(file, line);
			tmp.Id = StringToInt(line);
			
			getline(file, line);
			tmp.Product_name = line;
			
			getline(file, line);
			tmp.Category = line;
			
			getline(file, line);
			tmp.Price = StringToInt(line);
			
			getline(file, line);
			tmp.Description = line;
		
		}
		if (buf == "}")
		{
			Storage.push_back(tmp);
			tmp = DataStruct();
		}
	}
	file.close();

	cout << "файл был загружен!" << endl;
	WriteLine();

}

void SaveFile()
{
	ofstream file;
	file.open("Backup.buc");
	if (file.is_open() == false)
	{
		cout << "Файл не может быть открыт " << endl;
		return;
	}

	file << (int)Storage.size() << " Count" << endl;
	int i = 0;
	for (auto DataItem : Storage)
	{
		i++;
		file << "{" << endl
		    << DataItem.Id <<endl 
 			<< DataItem.Product_name << endl
			<< DataItem.Category << endl
			<< DataItem.Price << endl
			<< DataItem.Description << endl
			<< "}" << endl;
	}
	file.close();
	cout << "Файл был сохранен." << endl;
}

void UiFileContext()
{
	
	while (true)
	{
		WriteLine();
		cout
			<< "Работа с файлами ." << endl << endl
			<< "1) Загрузка. " << endl
			<< "2) Сохранение. " << endl
			<< "3) Назад. " << endl;
		WriteLine();
	    int result = selector();
		switch (result)
		{
		case 1:
		{
			LoadFile();
			break;
		}

		case 2:
		{
			SaveFile();
			break;
		}

		case 3:
		{
			break;
		}
		
		}
		
	}

}

int UiGetidToEdit()
{
	
	while (true)
	{
	    int result;
		WriteLine();
		cout << "Введите ID для изменения" << endl;
		result = selector();
		if ((result > Storage.size() || (result < 0)))
		{
			if (result == 0)
			{
				return 0;
			}
			cout << "ошибка не коректный ID" << endl;
		}
		else
		{
			WriteLine();
			return result;
		}
	
	}
}

void UiTableEditor()
{
	int result;

	WriteLine();
	cout
		<< "1) Добавление данных. " << endl
		<< "2) Изменение данных. " << endl
		<< "3) Удаление. " << endl
		<< "4) Выход. " << endl;
	WriteLine();
	result = selector();

	switch (result)
	{
	case 1:
	{
		Storage.push_back(AddData());
		break;
	}

	case 2:
	{
		int id = UiGetidToEdit();
		if (id == 0)
		{
			cout << "Отмена изменения." << endl;
			break;
		}
		Storage[id - 1] = EditStorage();
		break;
	}

	case 3:
	{
		int id = UiGetidToEdit();
		if (id == 0)
		{
			cout << "Отмена удаления." << endl;
			break;
		}
		Storage.erase(Storage.begin() + id - 1);
		cout << "данные удалены " << endl;
		break;
	}

	case 4:
	{
		
		break;
	}
	return;
	}

}

void WriteTable()
{
	WriteLine();
	int id = 0;
	cout << setw(4) << "Id" << '|'
		<< setw(25) << "название товара" << '|'
		<< setw(25) << "Категория " << '|'
		<< setw(10) << "цена" << '|'
		<< setw(30) << "описание" << '|'
	
		<< endl;
	for (auto DataItem : Storage)
	{
		id++;
		cout << setw(4) << id
			<< '|' << setw(4) << DataItem.Id
			<< '|' << setw(25) << DataItem.Product_name
			<< '|' << setw(25) << DataItem.Category
			<< '|' << setw(10) << DataItem.Price
			<< '|' << setw(30) << DataItem.Description << '|' << endl;
	}
	cout << endl << "...Конец таблицы." << endl;
	UiTableEditor();
	WriteLine();
}

void createData(int countFakeData)
{

	for (int i = 0; i < countFakeData; i++)
	{
		DataStruct tmp;
		tmp.Id = i;
		tmp.Product_name = "продукт " + IntToString(i);
		tmp.Category = "категория " + IntToString(i);
		tmp.Price = i;
		tmp.Description = "описание " +IntToString(i);

		Storage.push_back(tmp);
	}

}

int main()
{
	createData(150);
	setlocale(0, "russian");
	while (true)
	{
		int result;

		WriteLine();
		cout
			<< "База дынных" << endl << endl
			<< "1) Добавление данных. " << endl
			<< "2) Открытие таблицы. " << endl
			<< "3) Работа с Файлами. " << endl
			<< "4) Выход. " << endl;
		WriteLine();
		result = selector();

		switch (result)
		{
		case 1:
		{
			Storage.push_back(AddData());
			break;
		}

		case 2:
		{
			WriteTable();
			break;
		}

		case 3:
		{
			UiFileContext();
			break;
		}
		case 4:
		{
			
			break;
		}
     
		}

	}

}