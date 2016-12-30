/*
* member functions of class Account
*/

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <iomanip>
#include "Account.h"

using namespace std;

void Account::setBalance()
{
	CashBalance = 10000.0;
	storeBalance();
}
/*
void Account::changeBalance(double amount)
{
	CashBalance = 0;
	CashBalance = CashBalance + amount;
	storeBalance();
}
*/
double Account::getBalance() const
{
	return CashBalance;
}

void Account::storeBalance()
{
	ofstream ofile;
	ofile.open("bank_hist.txt");
	time_t seconds;
	tm *timeinfo;
	seconds = time(NULL);
	timeinfo = localtime(&seconds);
	ofile << getBalance() << "\t" << asctime(timeinfo) << endl;
	ofile.close();
}

bool Account::loadBalance()
{
	string str;
	string delimeter = "\t";
	string::size_type start = 0, index;
	string substr;
	int counter = 0;
	double balance = 0.0;

	ifstream ifile;
	ifile.open("bank_hist.txt");
	if (!ifile) {
		cout << "Cannot open file.\n";
		return false;
	}
	while (!ifile.eof())
	{
		getline(ifile, str);
		index = str.find_first_of(delimeter, start);
		while (index != string::npos) {
			substr = str.substr(start, index - start);
			if (counter % 2 == 0)
				balance = atof(substr.c_str());
			counter++;
			start = str.find_first_not_of(delimeter, index);
			if (start == string::npos)
				break;
			index = str.find_first_of(delimeter, start);
		}
		start = 0;

		CashBalance = balance;
		return true;
	}

	return false;
}