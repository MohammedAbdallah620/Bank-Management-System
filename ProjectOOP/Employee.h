#pragma once
#include <iostream>
#include <string> 
# include <map> 
# include <vector> 
#include "Customer.h"
# include "Account.h"
class Employee :public Customer
{
public:
	Employee() :Customer() {}
	void getReport_All_Customer();
	bool login_E(string u_n, string pass);
	~Employee();
};

