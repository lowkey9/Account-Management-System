/*
* Declaration of class BankAccount
* derived class of base class Account
*/

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include "Account.h"

class BankAccount : public Account
{
public:
	virtual void deposit();
	virtual void withdraw();
	virtual void viewBTHist();
};

#endif