#include <iostream>
#include <string>
#include <conio.h>
#include "Employee.h"
#include "Customer.h"
#include <ctime>
#include "Checking_Account.h"
#include "Saving_Account.h"
#include "loan_Account.h"
#include "Account.h"
using namespace std;
int main()
{
	while (true)
	{
		cout << "Do You Want To Loan Money OR Pay OFF A Loan y/n ? \n";
		char yes;
		cin >> yes;
		if (yes == 'y' || yes == 'Y')
		{
			loan_Account LA;
			cout <<"IF You Want To Loan Money press 1 , OR Pay OFF An Exist Loan press 2\n";
			int cc;
			cin >> cc;
			if (cc == 1)
			{
				cout << "Enter The Amount Of Money You Want To Loan \n";
				float loan_amount;
				cin >> loan_amount;
				cout << "Your Loan ID Is: " << LA.setData(loan_amount) << endl;
				cout<<" Please dont Forget The ID\n";
			}
			else if (cc == 2)
			{
				cout << "Enter The ID : ";
				int loanid;
				cin >> loanid;
				LA.PayOFF(loanid);
			}
		}
		cout << "If You Want to LogIn as a Customer press 1 , or Employee Press 2" << endl;
		int num;
		cin >> num;
		while (num != 1 && num != 2)
		{
			cout << "Please press number 1 if you are a Customer or 2 if you are an Employee" << endl;
			cin >> num;
		}
		string username, password = "";
		if (num == 1) // Customer log in
		{
			cout << "if you want to Enter to Loan System press L , or accounts press A " << endl;
			char C;
			cin >> C;
			Customer Cust;
			int i = 0;
			do
			{
				if (i)cout << "Invalid UserName Or Passward\n";
				cout << "Enter The UserName\n";
				cin >> username;
				char ch;
				cout << "Enter The UserName\n";
				ch = _getch();
				while (ch != 13)
				{
					password.push_back(ch);
					cout << '*';
					ch = _getch();
				}
				i++;
			} while (!Cust.login_C(username, password));
			cout << "Succeeded LogIn As an Employee\n";
			Cust.setdata(username, password);
			cout << "Do You Want To ADD New Account y/n ?? ";
			cin >> C;
			if (C == 'Y' || C == 'y')
			{
				time_t now;
				struct tm nowlocal;
				now = time(NULL);
				nowlocal = *localtime(&now);
				int Day = nowlocal.tm_mday, Month = nowlocal.tm_mon + 1, Year = nowlocal.tm_year + 1900;

				Account NewAccount;
				NewAccount.day = Day;
				NewAccount.month = Month;
				NewAccount.year = Year;
				cout << "Enter The Balance That You Want to Depsit It In The New Account \n";
				float bal;
				cin >> bal;
				NewAccount.balance = bal;
				cout << "Enter The Type Of  The New Account \n";
				string typ;
				cin >> typ;
				NewAccount.type = typ;
				Cust.add_new_account(NewAccount);

				cout << "The ID Of Your New Account is :  " << NewAccount.id << endl;
			}
			cout << "Do You Want to get Report About Your Accounts y/n ? " << endl;
			cin >> C;
			if (C == 'Y' || C == 'y')
			{
				Cust.getReport(username);
			}
			cout << "Do You Want deposit , withdraw or inquiry about the balance of an Exist Accout y/n ?" << endl;
			cin >> C;
			if (C == 'Y' || C == 'y')
			{
				int accountid, choice;
				do
				{
					cout << "Enter The ID Of The Account : ";
					cin >> accountid;
					cout << "If You Want to Deposit press 1 , withdraw press 2 or inquiry about the balance press 3 ";
					cin >> choice;
				} while (choice != 1 && choice != 2 && choice != 3);
				float lastbalance;
				if (choice == 1) // deposit
				{
					cout << "Enter The Money :";
					float money;
					cin >> money;

					lastbalance = Cust.deposit(accountid, money);
					Saving_Account sa;
					float F=sa.rate(accountid, lastbalance);
					cout << "Succeeded process" << endl;
				}
				else if (choice == 2) // withdraw
				{
					Checking_Account Ch_AC;
					int i = 0;
					bool ok = true;
					float amount;
					do
					{
						if (!i)cout << "Invalid Process , Too much Money" << endl;
						cout << "Do You Want To Withdraw Y/N? ";
						char c;
						cin >> c;
						if (c == 'n' || c == 'N')
						{
							ok = false;
							break;							
						}
						cout << "How much Money Would You Like To Withdraw ?" << endl;
						cin >> amount;
						i++;
					} while (!Ch_AC.withdraw(accountid, amount));

					if (ok)
					{
						cout << "Succeeded process , You Will Recieve " << amount << "Bounds" << endl;
					}
				}
				else if (choice == 3) // inquiry about the balance
				{
					cout << "Your Current Balance is Equal To: " << Cust.balance_inquiry(accountid) << endl;
				}
			}

		}

		else if (num == 2) // Employee log in
		{
			Employee emp;
			int i = 0;
			do
			{
				if (i)cout << "Invalid UserName Or Passward\n";
				password.clear();
				cout << "Enter The UserName\n";
				cin >> username;
				char ch;
				cout << "Enter pass\n";
				ch = _getch();
				while (ch != 13)
				{
					password.push_back(ch);
					cout << '*';
					ch = _getch();
				}

				i++;
			} while (!emp.login_E(username, password));


			cout << "Succeeded LogIn As an Employee\n";
			cout << "You Will Get All Reports About All Customers’ Accounts\n";

			emp.getReport_All_Customer();
		}

		cout << "Do You Want To continue y/n ??? " << endl;
		char c;
		cin >> c;
		if (c == 'N' || c == 'n')break;
	}
	return 0;
}