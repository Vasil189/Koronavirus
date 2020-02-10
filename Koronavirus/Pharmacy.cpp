// Pharmacy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include "Pharmacy.h"
#include "string"
#include "Admin.h"
#include <string.h>

using namespace std;

int main()
{
	fstream f;
	Pharmacy ph;
	///ph.CreateFile(f, "DataBase.txt", 2);
	//string q = "DataBase.txt";
	//ph.PrintFile(f, "DataBase.txt");
	//ph.SearchByForWhat(f, "DataBase.txt", "Pain");
	//ph.SearchByCost(f, "DataBase.txt", 10);
	//ph.CreateFile(f, q, 3);
	///ph.EditFile(f, "DataBase.txt", "");
	int a;
	cout << "Vuberit pid kum zahodute" << endl;
	cout << "1) Admin" << endl;
	cout << "2) Client" << endl;
	cin >> a;
	switch (a)
	{
	case 1:
		//TODO admin
		ph.Admin();
		break;
	case 2:
		//TODO user
	//default:
		break;
	}
	system("pause");
	return 0;
}



Pharmacy::Pharmacy()
{
}


Pharmacy::~Pharmacy()
{
}

void Pharmacy::InputDate(DATE& D)
{
	unsigned short temp;
	cout << "Input day : " << endl;
	cin >> temp;
	D.day = temp;
	cout << "Input month : " << endl;
	cin >> temp;
	D.month = temp;
	cout << "Input year : " << endl;
	cin >> temp;
	D.year = temp;
}

void Pharmacy::PrintDate(DATE D)
{
	cout << D.day << "." << D.month << "." << D.year << endl;
}

void Pharmacy::InputPreparat(PREPARAT& p)
{
	cout << "Input name : " << endl;
	std::getline(cin, p.Name);
	cout << "Input maker : " << endl;
	std::getline(cin, p.Maker);
	cout << "Input from what (Enter a word that is in < > " << endl;
	cout << "1) Headache <Headache> ; " << endl;
	cout << "2) Temperature <Temperature> ; " << endl;
	cout << "3) Pain in the stomach or abdomen <Pain> ; " << endl;
	cout << "4) Overeating <Overeating> ; " << endl;
	cout << "5) Ache <Ache> ; " << endl;
	cout << "6) Wellness <Wellness> ; " << endl;//Wellness - оздоровчі препарати
	cout << "7) Diseases <Diseases> : " << endl;//Diseases - від хвороб препарати (типу антибіотиків)
	getline(cin, p.FromWhat);
	cout << "Input cost : " << endl;
	cin >> p.Cost;
	cout << "Input the production date preparaty : " << endl;
	InputDate(p.start);
	cout << "Input expiration date preparaty : " << endl;
	InputDate(p.finish);
	cout << "Input count" << endl;
	cin >> p.count;
	cin.ignore();
	cout << endl << endl;
}

void Pharmacy::PrintPreparat(PREPARAT p)
{
	cout << "Name : " << p.Name << endl;
	cout << "Maker : " << p.Maker << endl;
	cout << "From what : " << p.FromWhat << endl;
	cout << "Cost : " << p.Cost << endl;
	cout << "Date of production : ";
	PrintDate(p.start);
	cout << "Date expiration : ";
	PrintDate(p.finish);
	cout << "Count :" << p.count << endl;
	cout << endl;
	cout << "====================================================" << endl << endl;
}

void Pharmacy::CreateFile(fstream& f, const char* filename, int size)
{
	f.open(filename, ios::out | ios::binary);
	for (int i = 0; i < size; i++)
	{
		PREPARAT p;
		InputPreparat(p);
		f.write(reinterpret_cast<char*>(&p), sizeof(p));
	}
	f.close();
}

void Pharmacy::PrintFile(fstream& f, const char* filename)
{
	f.open(filename, ios::in | ios::binary);
	if (f.is_open())
	{
		PREPARAT p;
		f.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!f.eof())
		{
			PrintPreparat(p);
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
		}
		f.close();
	}
	else
		cout << "Error (PrintFile) " << endl;
}

//TODO: add count
void Pharmacy::PrintCheck(fstream& f, const char* filename)
{
	int TCost = 0;
	char check = 'y';
	while (check == 'y' || check == 'Y')
	{
		cout << "Input name for preparat : " << endl;
		PREPARAT p;
		char name[20];
		cin.getline(name, 19);
		int pos = SearchByName(f, "DataBase.txt", name);
		if (pos >= 0)
		{
			f.open(filename, ios::in | ios::binary);
			f.seekg(pos * sizeof(p));
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
			cout << "Input count of preparat : " << endl;
			int k;
			cin >> k;
			int cost = p.Cost * k;
			cout << "Cost = " << cost << endl;
			f.close();
			TCost += cost;

		}
		else
			cout << "Not found preparat " << endl;

		cout << "Want you continion buy preparat (Input 'y' - yes or 'n' - no) " << endl;
		cin >> check;
		cin.ignore();
	}
	cout << "Total cost = " << TCost << endl;
}

int Pharmacy::Admin()
{
	Pharmacy pha;

	fstream f;
	string name_for_search;
	string forWhat_for_search;
	string maker_for_search;
	int cost_for_search;
	int count_for_search;
	string name_for_delete_preparat;


	string password = "2020";
	string pass;
	cout << "Input password" << endl;
	cin >> pass;
	if (pass == password)
	{
		int q;
		cout << "Vxid uspishnuy" << endl;
		cout << "Vuberit sho vu hochete zrobutu (zufru)" << endl;
		cout << "1)Poshyk po preparatam" << endl;
		cout << "2)Sortuvanya po preparatam" << endl;
		cout << "3)Vuvid basu preparativ" << endl;
		cout << "4)Udalut preparat" << endl;
		cout << "5)Dodatu aparat" << endl;
		cout << "6)Udalut clienta" << endl;
		cout << "7)Ban clientow" << endl;
		cout << "8)Vuvid basu clientiw" << endl;
		cin >> q;
		switch (q)
		{
		case 1:
			int shearch;
			cout << "Poshuk po :" << endl;
			cout << "1)Name" << endl;
			cout << "2)Ot chego" << endl;
			cout << "3) Cost " << endl;
			cout << "4)Maker" << endl;
			cout << "5) Kilkist" << endl;
			cin >> shearch;
			switch (shearch)
			{
			case 1:
				cout << "Input name" << endl;
				cin >> name_for_search;
				//char* c = strcpy(new char[name_for_search.length() + 1], name_for_search.c_str());
				//char* c = strcpy_s(new char[name_for_search.length() + 1], name_for_search.c_str());
				//int p = name_for_search.length() + 1;
				//int p = sizeof(name_for_search.c_str());
				//char* c = strcpy_s(new char[name_for_search.length() + 1][p], name_for_search.c_str());
				//char* c = strcpy_s(char(&(name_for_search.length() + 1)[sizeof name_for_search.length]), name_for_search.c_str());

				//pha.SearchByName(f, "DataBase.txt", p);
				break;
			case 2:
				cout << "Input od chogo" << endl;
				cin >> forWhat_for_search;
				//char* a = strcpy(new char[forWhat_for_search.length() + 1], forWhat_for_search.c_str());
				//pha.SearchByForWhat(f, "DataBase.txt", a);
				break;
			case 3:
				cout << "Input maker" << endl;
				cin >> maker_for_search;
				//char* b = strcpy(new char[maker_for_search.length() + 1], maker_for_search.c_str());
				//pha.SearchByMaker(f, "DataBase.txt", b);
				break;
			case 4:
				cout << "Input cost" << endl;
				cin >> cost_for_search;
				pha.SearchByCost(f, "DataBase.txt", cost_for_search);
				break;
			case 5:
				cout << "Input count" << endl;
				cin >> count_for_search;
				pha.SearchByCount(f, "DataBase.txt", count_for_search);
				break;
			default:
				cout << "Error switch(search)" << endl;
				break;
			}
			break;
		case 2:
			int sort;
			cout << "Sortirovka po :" << endl;
			cout << "1)Name" << endl;
			cout << "2)Cost" << endl;
			cout << "3)Count" << endl;
			cin >> sort;
			switch (sort)
			{
			case 1:
				pha.SortByName(f, "DataBase.txt", "Sort_by_name.txt");
				break;
			case 2:
				pha.SortByCost(f, "DataBase.txt", "Sort_by_cost.txt");
				break;
			case 3:
				pha.SortByCount(f, "DataBase.txt", "Sort_by_count.txt");
				break;
			default:
				cout << "Error Admin sort" << endl;
				break;
			}
			break;
		case 3:
			pha.PrintFile(f, "DataBase.txt");
			break;
		case 4:
			cout << "Input name" << endl;
			cin >> name_for_delete_preparat;
			//char* w = strcpy(new char[name_for_delete_preparat.length() + 1], name_for_delete_preparat.c_str());
			//pha.DeletePreparat(f, "DataBase.txt", w);
			break;
		case 5:
			pha.AppendPreparat(f, "DataBase.txt");
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		default: cout << "Error vubor v admina" << endl;
			break;
		}
	}
	else
	{
		cout << "Parol nepravilnuy" << endl;
	}

	return 0;
}

int Pharmacy::SearchByName(fstream& f, const char* filename, char* name)
{
	int pos = 0;
	f.open(filename, ios::in | ios::binary);
	if (f.is_open())
	{
		PREPARAT p;
		f.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!f.eof())
		{
			if (p.Name == name)
			{
				PrintPreparat(p);
				f.close();
				return pos;
			}
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
			pos++;
		}
		cout << "Preparat for name not found " << endl;
		f.close();
		return -1;
	}
	else
		cout << "Error (SearchByName) " << endl;
	//return 0;
}

int Pharmacy::SearchByForWhat(fstream& f, const char* filename, const char* FORWHAT)//Пошук від чого препарат
{
	int pos = 0;
	f.open(filename, ios::in | ios::binary);
	if (f.is_open())
	{
		PREPARAT p;
		f.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!f.eof())
		{
			if (p.FromWhat == FORWHAT)
			{
				PrintPreparat(p);
				f.close();
				return pos;
			}
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
			pos++;
		}
		cout << "Preparet for what not found " << endl;
		f.close();
		return -1;
	}
	else
		cout << "Error (SearchByForWhat) " << endl;
}

int Pharmacy::SearchByCost(fstream& f, const char* filename, int COST)
{
	int pos = 0;
	f.open(filename, ios::in | ios::binary);
	if (f.is_open())
	{
		PREPARAT p;
		f.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!f.eof())
		{
			if (p.Cost >= COST * 0.9 && p.Cost <= COST * 1.1)
			{
				PrintPreparat(p);
				f.close();
				return pos;
			}
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
			pos++;
		}
		cout << "Preparet for cost not found " << endl;
		f.close();
		return -1;
	}
	else
		cout << "Error (SearchByCost) " << endl;
	//return 0;
}

int Pharmacy::SearchByCount(fstream& f, const char* filename, int COUNT)
{
	int pos = 0;
	f.open(filename, ios::in | ios::binary);
	if (f.is_open())
	{
		PREPARAT p;
		f.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!f.eof())
		{
			if (p.Cost >= COUNT * 0.9 && p.Cost <= COUNT * 1.1)
			{
				PrintPreparat(p);
				f.close();
				return pos;
			}
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
			pos++;
		}
		cout << "Preparet for count not found " << endl;
		f.close();
		return -1;
	}
	else
		cout << "Error (SearchByCount) " << endl;
	//return 0;
}

int Pharmacy::SearchByMaker(fstream& f, const char* filename, const char* MAKER)
{
	int pos = 0;
	f.open(filename, ios::in | ios::binary);
	if (f.is_open())
	{
		PREPARAT p;
		f.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!f.eof())
		{
			if (p.Maker == MAKER)
			{
				PrintPreparat(p);
				//system("pause");
				f.close();
				return pos;
			}
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
			pos++;
		}
		cout << "Preparat for maker not found " << endl;
		f.close();
		return -1;
	}
	else
		cout << "Error (SearchByMaker) " << endl;
	//return 0;
}

void Pharmacy::EditFile(fstream& f, const char* filename, char* Name)
{
	int pos = SearchByName(f, filename, Name);
	if (pos < 0)
	{
		return;
	}

	f.open(filename, ios::in | ios::out | ios::binary);
	f.seekg(pos * sizeof(PREPARAT), ios::beg);
	PREPARAT p;
	f.read(reinterpret_cast<char*>(&p), sizeof(p));
	cout << "Edit : 1.Name, 2.Maker, 3.FromWhat, 4.cost, 5.start (date), 6.finish (date) 7.Count" << endl;
	int menu;
	cin >> menu;
	switch (menu)
	{
	case 1:
		cout << "Input new name : " << endl;
		cin.ignore();
		getline(cin, p.Name);
		break;
	case 2:
		cout << "Input new maker : " << endl;
		cin.ignore();
		getline(cin, p.Maker);
		break;
	case 3:
		cout << "Input new Frow What : " << endl;
		cin.ignore();
		getline(cin, p.FromWhat);
		break;
	case 4:
		cout << "Input new cost : " << endl;
		cin >> p.Cost;
		break;
	case 5:
		cout << "Input new date (strart) : " << endl;
		InputDate(p.start);
		break;
	case 6:
		cout << "Input new date (finish) : " << endl;
		InputDate(p.finish);
		break;
	case 7:
		cout << "Input new count : " << endl;
		cin.ignore();
		cin >> p.count;
		break;
	default:
		cout << "Error (EditFile(switch)) : " << endl;
		break;
	}
	f.seekp(pos * sizeof(PREPARAT), ios::beg);
	f.write(reinterpret_cast<char*>(&p), sizeof(p));
	f.close();
}

void Pharmacy::SortByName(fstream& f, const char* filename, const char* filenameRes)
{
	f.open(filename, ios::in | ios::binary);
	if (!f.is_open())
	{
		return;
	}
	f.seekg(0, ios::end);
	int N = f.tellg() / sizeof(PREPARAT);
	f.clear();
	f.seekg(0, ios::beg);
	PREPARAT* arr = new PREPARAT[N];
	f.read(reinterpret_cast<char*>(arr), sizeof(PREPARAT)* N);//сортування 2 спосіб
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (arr[j].Name == arr[j + 1].Name)
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}

	fstream f1(filenameRes, ios::out | ios::binary);
	for (int i = 0; i < N; i++)
		f1.write(reinterpret_cast<char*>(&arr[i]), sizeof(PREPARAT));
	f.close();
	f1.close();
}

void Pharmacy::SortByCost(fstream& f, const char* filename, const char* filenameRes)
{
	f.open(filename, ios::in | ios::binary);
	if (!f.is_open())
	{
		return;
	}
	f.seekg(0, ios::end);
	int N = f.tellg() / sizeof(PREPARAT);
	f.clear();
	f.seekg(0, ios::beg);
	PREPARAT* arr = new PREPARAT[N];	
	f.read(reinterpret_cast<char*>(arr), sizeof(PREPARAT)* N);//сортування 2 спосіб
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (arr[j].Cost > arr[j + 1].Cost)
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}

	fstream f1(filenameRes, ios::out | ios::binary);
	for (int i = 0; i < N; i++)
		f1.write(reinterpret_cast<char*>(&arr[i]), sizeof(PREPARAT));
	f.close();
	f1.close();
}

void Pharmacy::SortByCount(fstream& f, const char* filename, const char* filenameRes)
{
	f.open(filename, ios::in | ios::binary);
	if (!f.is_open())
	{
		return;
	}
	f.seekg(0, ios::end);
	int N = f.tellg() / sizeof(PREPARAT);
	f.clear();
	f.seekg(0, ios::beg);
	PREPARAT* arr = new PREPARAT[N];
	f.read(reinterpret_cast<char*>(arr), sizeof(PREPARAT)* N);//сортування 2 спосіб
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (arr[j].count > arr[j + 1].count)
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}

	fstream f1(filenameRes, ios::out | ios::binary);
	for (int i = 0; i < N; i++)
		f1.write(reinterpret_cast<char*>(&arr[i]), sizeof(PREPARAT));
	f.close();
	f1.close();
}

void Pharmacy::DeletePreparat(fstream& f, const char* filename, char* name)
{
	fstream f1("Temp.txt", ios::out | ios::binary);
	f.open(filename, ios::in | ios::binary);
	int del = 0;
	if (f.is_open())
	{
		PREPARAT p;

		f.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!f.eof())
		{
			if (p.Name != name)
			{
				f1.write(reinterpret_cast<char*>(&p), sizeof(p));
			}
			else del++;
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
		}
		if (del > 0) cout << "Deleted OK " << endl;
		else cout << "deleted not " << endl;
		f.close();
	}
	else
		cout << "Error (DeleteByName) " << endl;
	f1.close();
	if (del > 0)
	{
		remove(filename);
		rename("Temp.txt", filename);
	}
}

int Pharmacy::SearchByDate(fstream& f, char* filename, DATE d)
{
	int pos = 0;
	f.open(filename, ios::in | ios::binary);
	if (f.is_open())
	{
		PREPARAT p;
		f.read(reinterpret_cast<char*>(&p), sizeof(p));
		while (!f.eof())
		{
			if (p.finish.day == d.day && p.finish.month == d.month && p.finish.year == d.year)
			{
				PrintPreparat(p);
				f.close();
				return pos;
			}
			f.read(reinterpret_cast<char*>(&p), sizeof(p));
			pos++;
		}
		cout << "Date not found " << endl;
		f.close();
		return -1;
	}
	else
		cout << "Error (SearchByDate) " << endl;
	//return 0;
}

void Pharmacy::AppendPreparat(fstream& f, const char* filename)
{

	f.open(filename, ios::binary | ios::app);
	if (f.is_open())
	{
		PREPARAT p;
		InputPreparat(p);
		f.write(reinterpret_cast<char*>(&p), sizeof(p));
		f.close();
	}
	else
		cout << "Eror (AppendPreparat) " << endl;
}

