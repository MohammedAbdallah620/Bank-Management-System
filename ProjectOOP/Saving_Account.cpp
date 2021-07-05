#include "Saving_Account.h"
# include <list>
# include < ctime>
# include <fstream>
# include <iostream>
#include <ostream>
# include <string> 
#include"Account.h"

int Saving_Account::getdata(int i_d)
{
	mymap = read_acc();

	bool flag = false;
	time_t now;
	struct tm nowlocal;
	now = time(NULL);
	nowlocal = *localtime(&now);
	int DAY = 0, MONTH = 0, YEAR = 0;
	string s = mymap[i_d].second[0];
	string d, m, y;

	DAY = ((int)(s[0] - '0')) * 10 + ((int)(s[1] - '0'));
	MONTH = ((int)(s[3] - '0')) * 10 + ((int)(s[4] - '0'));
	YEAR = ((int)(s[6] - '0')) * 1000 + ((int)(s[7] - '0')) * 100 + ((int)(s[8] - '0')) * 10 + ((int)(s[9] - '0'));
	int  total_day = nowlocal.tm_mday - DAY;
	int  total_mon = nowlocal.tm_mon + 1 - MONTH;
	int  total_year = nowlocal.tm_year + 1900 - YEAR;

	int No_Of_month = total_year * 12;
	No_Of_month += total_mon;
	return No_Of_month;
}


float Saving_Account::rate(int I_d, float bal)
{
	float ff = bal;
	int No_Of_month = getdata(I_d);
	for (int i = 0; i < No_Of_month; i++)
	{
		interest_Rate = 0.2*bal;
		bal += interest_Rate;
	}
	mymap[I_d].first = bal;
	ofstream myfile("accounts.txt", ios::out);
	string S = "id";
	for (it = mymap.begin(); it != mymap.end(); it++)
	{
		myfile << S << '\n';
		myfile << it->first << '\n';
		myfile << it->second.first << '\n';
		for (int i = 0; i < it->second.second.size(); i++)
		{
			myfile << it->second.second[i] << '\n';
		}
	}
	return bal-ff;
	myfile.close();
}
Saving_Account::~Saving_Account()
{
}

























