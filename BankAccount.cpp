/*
* member function of class BankAccount
* derived class of base class Account
*/

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <iomanip>
#include "BankAccount.h"

using namespace std;

void BankAccount::deposit()
{
	/*deposit money*/
	double amount = 0.0;
	cout << "Please enter the amount you wish to deposit: ";
	cin >> amount;
	CashBalance += amount;

	/*record deposit history*/
	time_t seconds;
	tm *timeinfo;
	ofstream ofile;
	ofile.open("bank_transaction_history.txt", ios::app);
	seconds = time(NULL);
	timeinfo = localtime(&seconds);
	ofile << "DEPOSIT" << setw(15) << amount << setw(20) << asctime(timeinfo) << setw(15) << getBalance() << endl;
}

void BankAccount::withdraw()
{
	/*withdraw money*/
	double amount = 0.0;
	cout << "Please enter the amount you wish to withdraw: ";
	cin >> amount;
	double curBalance = 0.0;
	curBalance = getBalance();
	if (amount > curBalance) {
		cout << "Your cash balance is not sufficient.\nWithdraw Failed!\n";
		return;
	}
	else {
		CashBalance -= amount;

		/*record withdraw history*/
		time_t seconds;
		tm *timeinfo;
		ofstream ofile;
		ofile.open("bank_transaction_history.txt", ios::app);
		seconds = time(NULL);
		timeinfo = localtime(&seconds);
		ofile << "WITHDRAW" << setw(25) << amount << setw(20) << asctime(timeinfo) << setw(15) << getBalance() << endl;
	}
}

void BankAccount::viewBTHist()
{
	string str;
	ifstream ifile;
	ifile.open("bank_transaction_history.txt");
	cout << endl;
	while (!ifile.eof()) {
		getline(ifile, str);
		cout << str << endl;
	}
	ifile.close();
}