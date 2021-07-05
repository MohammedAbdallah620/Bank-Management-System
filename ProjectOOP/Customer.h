#pragma once 
#include <iostream>
#include "Account.h"
#include <string> 
# include <map> 
# include <vector>
using namespace std;

class Customer : public Account
{
	string username_customer;
	string password_customer;
public:
	

	Customer() : Account() {}
	bool login_C(string u_n, string pass);
	void setdata(string un, string pass);
	void add_new_account(Account A);
	void getReport(string u_n);
};

