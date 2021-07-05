
#pragma once
#include <iostream>
#include <string> 
# include <map> 
# include <vector>
# include "Account.h"
using namespace std;
class Saving_Account : public Account
{
	float interest_Rate;
public:
	map<int, pair<float, vector<string>>> mymap;
	map<int, pair<float, vector<string>>> ::iterator it;
	Saving_Account() : Account() {

		interest_Rate = (float)0.2;
	}

	int getdata(int i_d);
	float rate(int I_d, float bal);

	~Saving_Account();
};

