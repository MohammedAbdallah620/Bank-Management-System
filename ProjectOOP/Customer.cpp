#include "Customer.h"
#include<fstream>
#include <string>
string to_string(float val);
string to_string(int val);



bool Customer::login_C(string u_n, string pass)
{
	fstream myfile;
	myfile.open("login_customers.txt");
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
void Customer::setdata(string u_n, string pass)
{
	this->username_customer = u_n;
	this->password_customer = pass;
}



void Customer::add_new_account(Account A)
{
	map < string, vector<int> > mp=read_id();
	map < string, vector<int> >::iterator it;
	map<int, pair<float, vector<string>>> mmp = read_acc();
	bool flag = false;
	for (it = mp.begin(); it != mp.end(); it++)
	{
		if ((it->first) == username_customer)
		{
			flag = true;
			it->second.push_back(A.id);
			break;
		}
	}
	if (!flag)
	{
		vector<int>v;
		v.push_back(A.id);
		mp[username_customer] = v;
	}

	ofstream myfile("customers.txt",ios::out);
	string s = "username";
	for (it = mp.begin(); it!=mp.end(); it++)
	{
		myfile << s << '\n';
		myfile << it->first << '\n';
		for (int i = 0;  i < it->second.size(); i++)
		{
			myfile << it->second[i] << '\n';
		}
	}
	myfile.close();
	fstream mynewfile("accounts.txt" , ios::app);
	string S = "id";
	mynewfile <<'\n' << S << '\n';
	mynewfile << A.id << '\n';
	mynewfile << A.balance << '\n';
	string Dat = "";
	if (A.day / 10 == 0) 
	{
		Dat += "0";
		char c = (char) A.day + '0';
		Dat += c;
	}
	else
	{
		string t = std::to_string(A.day) + "";
		Dat += t;
	}
	Dat += "/";
	if (A.month / 10 == 0)
	{
		Dat += "0";
		char c = (char)A.month+ '0';
		Dat += c;
	}
	else
	{
		string t = std::to_string(A.month) + "";
		Dat += t;
	}
	Dat += "/";
	string t = std::to_string(A.year) + "";
	Dat += t;
	mynewfile << Dat << '\n';
	string T = "type:" + A.type;
	mynewfile << T;
	vector<string> v;
	v.push_back(Dat);
	v.push_back(A.type);
	mmp[A.id] = make_pair(A.balance, v);
	mynewfile.close();
}

void Customer::getReport(string u_n)
{
	map<int, pair<float, vector<string>>> ma = read_acc();
	map<string,vector<int>> mp=read_id();
	vector<int>v = mp[u_n];
	cout << u_n << endl;
	for (int i=0 ; i< v.size(); i++)
	{

		cout << "Accont ID Is:" << v[i]<<endl;
		cout << "Current Balance Is:" << ma[v[i]].first << endl;
		for (int j = 0; j < ma[v[i]].second.size(); j++)
		{
			if(ma[v[i]].second[j]!="")cout << ma[v[i]].second[j] << endl;
		}
		cout << endl;
	}
}

