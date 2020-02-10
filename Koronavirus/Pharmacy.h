#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "Admin.h"

using namespace std;

class Pharmacy
{
public:
	Pharmacy();
	~Pharmacy();

	void CreateFile(fstream& f, const char* filename, int size);//Створення файлу
	void PrintFile(fstream& f, const char* filename);//Виведення файлу
	void EditFile(fstream& f, const char* filename,  char* Name);//Редагування файла

	int SearchByName(fstream& f, const char* filename, char* name);//Пошук за назвою
	int SearchByForWhat(fstream& f, const char* filename, const char* FORWHAT);//Пошук від чого препарат
	int SearchByCost(fstream& f, const char* filename, int COST);//Пошук по ціні 
	int SearchByMaker(fstream& f, const char* filename, const char* MAKER);//Пошук за виробником
	int SearchByCount(fstream& f, const char* filename, int COUNT);

	void SortByName(fstream& f, const char* filename, const char* filenameRes);//Сортування за назвою
	void SortByCost(fstream& f, const char* filename, const char* filenameRes);//Сортування за ціною
	void SortByCount(fstream& f, const char* filename, const char* filenameRes);//Сортування за кількісю

	void DeletePreparat(fstream& f, const char* filename, char* name);//Видалення по назві
	void AppendPreparat(fstream& f, const char* filename);//Додавання препарату

	void PrintCheck(fstream& f, const char* filename);

	int Admin();
private:
	struct DATE
	{
		unsigned short day : 5;
		unsigned short month : 4;
		unsigned short year : 11;
	};

	struct PREPARAT
	{
		string Name;
		string Maker;
		string FromWhat;
		int Cost;
		DATE start;
		DATE finish;
		int count;
	};

	void InputDate(DATE& D);//Ввід дати

	void PrintDate(DATE D);//Вивід дати	

	void InputPreparat(PREPARAT& p);//Введення препарату	

	void PrintPreparat(PREPARAT p);//Вивід препарату
	int SearchByDate(fstream& f, char* filename, DATE d);//Пошук по даті



};

