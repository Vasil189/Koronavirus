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

	void CreateFile(fstream& f, const char* filename, int size);//��������� �����
	void PrintFile(fstream& f, const char* filename);//��������� �����
	void EditFile(fstream& f, const char* filename,  char* Name);//����������� �����

	int SearchByName(fstream& f, const char* filename, char* name);//����� �� ������
	int SearchByForWhat(fstream& f, const char* filename, const char* FORWHAT);//����� �� ���� ��������
	int SearchByCost(fstream& f, const char* filename, int COST);//����� �� ��� 
	int SearchByMaker(fstream& f, const char* filename, const char* MAKER);//����� �� ����������
	int SearchByCount(fstream& f, const char* filename, int COUNT);

	void SortByName(fstream& f, const char* filename, const char* filenameRes);//���������� �� ������
	void SortByCost(fstream& f, const char* filename, const char* filenameRes);//���������� �� �����
	void SortByCount(fstream& f, const char* filename, const char* filenameRes);//���������� �� ������

	void DeletePreparat(fstream& f, const char* filename, char* name);//��������� �� ����
	void AppendPreparat(fstream& f, const char* filename);//��������� ���������

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

	void InputDate(DATE& D);//��� ����

	void PrintDate(DATE D);//���� ����	

	void InputPreparat(PREPARAT& p);//�������� ���������	

	void PrintPreparat(PREPARAT p);//���� ���������
	int SearchByDate(fstream& f, char* filename, DATE d);//����� �� ���



};

