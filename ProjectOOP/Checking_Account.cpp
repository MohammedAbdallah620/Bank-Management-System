#include "Checking_Account.h"
#include <iostream>
#include<string>
#include<fstream>
#include "Saving_Account.h"
using namespace std;
string to_string(float val);
bool Checking_Account::withdraw(int iD ,float fund)
{
	map<int, pair<float, vector<string>>> mp = read_acc();
	map<int, pair<float, vector<string>>>::iterator it;
	creditlimit = (float)(0.2 * mp[iD].first);
	float x=mp[iD].first;
	Saving_Account SA;
	float rat= SA.rate(iD, fund);
	if (fund > creditlimit + mp[iD].first+rat || mp[iD].first+rat<1)
	{
		return false;
	}
	else
	{
		mp = read_acc();
		if (mp[iD].first >= fund)mp[iD].first -= fund;
		else
		{
			mp[iD].first -= fund;
			creditlimit += mp[iD].first;
		}
		string s = "withdraw:";
		string t = std::to_string(fund) + "";
		s += t;
		mp[iD].second.push_back(s);
		ofstream myfile("accounts.txt", ios::out);
		string ss = "id";
		for (it = mp.begin(); it != mp.end(); it++)
		{
			myfile << ss << '\n';
			myfile << it->first << '\n';
			myfile << it->second.first << '\n';
			for (int i = 0; i < it->second.second.size(); i++)
			{
				myfile << it->second.second[i] << '\n';
			}
		}
		myfile.close();
		return true;
	}
}
