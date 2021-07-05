#include <string> 
# include <map> 
# include <vector>
# include "Account.h"
class loan_Account :public Account
{
	float principal_amount, interest_rate;
	int loan_duration;
	float loan_balance;
public:
	loan_Account() :Account()
	{
		loan_duration = 10;
	}
	int setData(int loan_bal);
	void PayOFF(int I_d);
	string castDate(int d, int m, int y);
};
