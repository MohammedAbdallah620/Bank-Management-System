#include "Employee.h"
#include <string> 
#include<fstream>

bool Employee::login_E(string u_n, string pass)
{
	bool check = false;

	fstream myfile;
	myfile.open("login_employees.txt");
	string username, password;
	int i = 0;
	bool find = false;

	while (!myfile.eof())
	{
		if (i % 2 == 0)
		{
			getline(myfile, username);
			if (username == "") { break; }
		}
		else
		{
			getline(myfile, password);
			if (password == "") { break; }
			if (username == u_n&&password == pass) { find = true;	break; }
		}
		i++;
	}
	if (find)return true;
	else return false;
}

void Employee::getReport_All_Customer() 
{
	map<string , vector<int>>mp=read_id();
	map<string, vector<int>>::iterator it;
	for (it = mp.begin(); it != mp.end(); it++)
	{
		getReport(it->first);
	}
}
Employee::~Employee()
{
}
 