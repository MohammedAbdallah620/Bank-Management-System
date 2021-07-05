#pragma once
# include "Account.h"
#include <iostream>
#include <string> 
# include <map> 
# include <vector>
using namespace std;

class Checking_Account : public Account
{

public:
	float creditlimit;
	Checking_Account() :Account() { creditlimit = 0; }
	bool withdraw(int iD,float fund);

};




