#pragma once
#include <iostream>
#include <string> 
# include <map> 
# include <vector>
#include <fstream>
using namespace std;
class Account
{
public:
	float balance;
	int day, year, month;
	string  type;
	 int id;
	Account()
	{
		balance = 0.0;
		day = year = month = 0;
		type = "";
		fstream idfile("staticid.txt", ios::in);
		idfile >> id;
		id++;
		idfile.close();
		fstream file("staticid.txt", ios::out);
		file << id;
		file.close();
	}
	float deposit(int iD,float  Bala);
	float balance_inquiry(int iD);
	map<int, pair<float, vector<string>>> read_acc();
	map<string, vector<int>>read_id();
	~Account();
};

