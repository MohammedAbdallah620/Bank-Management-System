#include "Account.h"
#include <iostream>
# include <fstream>
#include <ostream>
# include <string>
#include "Saving_Account.h"
string to_string(float val);


float Account::deposit(int iD , float Bala) 
{
	map<int, pair<float, vector<string>>> mp = read_acc();
	map<int, pair<float, vector<string>>>::iterator it;
	float lastbalance=mp[iD].first;
	mp[iD].first += Bala;
	string s="depsit:";
	string t = std::to_string(Bala) + "";
	s += t;
	mp[iD].second.push_back(s);
	ofstream myfile("accounts.txt", ios::out);
	string ss = "id";
	for (it = mp.begin(); it != mp.end(); it++)
	{
		myfile << ss << '\n';
		myfile << it->first << '\n';
		myfile << it->second.first<<'\n';
		for (int i = 0; i < it->second.second.size(); i++)
		{
			myfile << it->second.second[i] << '\n';
		}
	}
	myfile.close();
	return lastbalance;
}

float  Account::balance_inquiry(int iD)
{
	map<int, pair<float, vector<string>>> mp = read_acc();
	map<int, pair<float, vector<string>>>::iterator it;
	string s = "balanceinquiry:";
	string t = std::to_string(mp[iD].first) + "";
	s += t;
	mp[iD].second.push_back(s);
	ofstream myfile("accounts.txt", ios::out);
	string S = "id";
	for (it = mp.begin(); it != mp.end(); it++)
	{
		myfile << S << '\n';
		myfile << it->first << '\n';
		myfile << it->second.first << '\n';
		for (int i = 0; i < it->second.second.size(); i++)
		{
			myfile << it->second.second[i] << '\n';
		}
	}
	myfile.close();
	Saving_Account SA;
	float rat=SA.rate(iD, mp[iD].first);
	return (mp[iD].first+rat);
}

map<int, pair<float, vector<string>>> Account::read_acc()
{
	map<int, pair<float,vector<string>>> mymap;
	fstream myfile;
	myfile.open("accounts.txt");
	string line , date;
	int id;
	float CurrentBalance;
	getline(myfile, line);
	while (!myfile.eof())
	{
		vector<string> vec;
		if (line== "id")
		{
			myfile >> id;
			myfile >> CurrentBalance;
			/*myfile >> date;
			vec.push_back(date);*/
			line = "";
		}
		else
		{
			while (!myfile.eof())
			{
				getline(myfile, line);
				if (line == "id")break;
				vec.push_back(line);
			}
		}
		mymap[id] = make_pair(CurrentBalance , vec);
	}
	return mymap;
}

map<string, vector<int>> Account::read_id()
{
	map<string, vector<int>>mp;
	fstream myfile;
	myfile.open("customers.txt");
	string username, line;

	getline(myfile, line);
	while (!myfile.eof())
	{
		vector<int> vec;
		if (line == "username")
		{
			getline(myfile, username);
			line = "";
		}
		else
		{
			while (!myfile.eof())
			{
				getline(myfile, line);

				if (line == "username")break;

				int x = 1;
				int sum = 0;
				for (int i = line.size() - 1; i >= 0; i--)
				{
					int y = line[i] - '0';
					sum += (y*x);
					x *= 10;
				}
				vec.push_back(sum);
			}
			mp[username] = vec;
		}
	}
	return mp;
}

Account::~Account()
{
}
