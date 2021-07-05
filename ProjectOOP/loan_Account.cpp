#include "loan_Account.h"
# include <fstream>
# include <iostream>
#include <ostream>
# include <string> 
# include "Account.h"
# include <ctime>
string to_string(int val);


string loan_Account::castDate(int d, int m, int y)
{
	string Dat = "";
	if (d / 10 == 0)
	{
		Dat += "0";
		char c = (char)d + '0';
		Dat += c;
	}
	else
	{
		string t = std::to_string(d) + "";
		Dat += t;
	}
	Dat += "/";
	if (m / 10 == 0)
	{
		Dat += "0";
		char c = (char)m+ '0';
		Dat += c;
	}
	else
	{
		string t = std::to_string(m) + "";
		Dat += t;
	}
	Dat += "/";
	string t = std::to_string(y) + "";
	Dat += t;
	return Dat;
}
int loan_Account::setData(int loan_bal)
{
	this->loan_balance = loan_bal;
	this->principal_amount = loan_bal / 10;
	time_t now;
	struct tm nowlocal;
	now = time(NULL);
	nowlocal = *localtime(&now);
	this->day = nowlocal.tm_mday;
	this->month = nowlocal.tm_mon + 1;
	this->year = nowlocal.tm_year + 1900;
	cout << this->day << " " << this->month << " " << this->year << endl;
	fstream idfile("staticid.txt", ios::in);
	idfile >> id;
	id++;
	idfile.close();
	cout << this->id;
	fstream file("staticid.txt", ios::out);
	file << id;
	file.close();

	fstream mynewfile("loan.txt", ios::app);
	string Dat = castDate(this->day , this->month , this->year);
	// write in file
	mynewfile << '\n'<< this->id << '\n';
	mynewfile << loan_bal << '\n';
	mynewfile << this->principal_amount << '\n';
	mynewfile << Dat;

	cout << "You must Pay Off " << this->principal_amount<<" Every Month For 10 Months."<< endl;
	return this->id;
}

void loan_Account::PayOFF(int I_d)
{
	fstream loanfile("loan.txt", ios::in);
	map<int, pair<pair<float, float>, string>> loanmap;
	map<int, pair<pair<float, float>, string>>::iterator it;
	int iid;
	float bal, princ;
	string datee;
	while (loanfile >> iid >> bal >> princ >> datee)
	{
		loanmap[iid] = make_pair(make_pair(bal, princ), datee);
	}
	loanfile.close();
	time_t now;
	struct tm nowlocal;
	now = time(NULL);
	nowlocal = *localtime(&now);
	this->day = nowlocal.tm_mday;
	this->month = nowlocal.tm_mon + 1;
	this->year = nowlocal.tm_year + 1900;
	datee = loanmap[I_d].second;

	int DAY = ((int)(datee[0] - '0')) * 10 + ((int)(datee[1] - '0'));
	int MONTH = ((int)(datee[3] - '0')) * 10 + ((int)(datee[4] - '0'));
	int YEAR= ((int)(datee[6] - '0')) * 1000 + ((int)(datee[7] - '0')) * 100 + ((int)(datee[8] - '0')) * 10 + ((int)(datee[9] - '0'));

	int  total_day = nowlocal.tm_mday - DAY;
	int  total_mon = nowlocal.tm_mon + 1 - MONTH;
	int  total_year = nowlocal.tm_year + 1900 - YEAR;
	int No_Of_month = total_year * 12;
	No_Of_month += total_mon;
	if( (No_Of_month > 1)||(No_Of_month == 1 && total_day>0))
	{
		cout <<"You Will Pay A Fine : "<< 0.1*loanmap[I_d].first.first*No_Of_month <<endl;
		loanmap[I_d].first.first += ((float)(0.1*loanmap[I_d].first.first)*No_Of_month);
	}
	loanmap[I_d].first.first -= (loanmap[I_d].first.second*No_Of_month);

	MONTH++;
	if (MONTH == 13)
	{
		MONTH = 1;
		YEAR++;
	}
	string Dat = castDate(this->day, this->month, this->year);
	loanmap[I_d].second = Dat;

	fstream file("loan.txt", ios::out);

	for (it = loanmap.begin(); it != loanmap.end(); it++)
	{
		if (it == loanmap.begin())file << it->first<<'\n';
		else file <<'\n'<< it->first << '\n';
		file << it->second.first.first << '\n';
		file << it->second.first.second << '\n';
		file << it->second.second;
	}
	file.close();
}