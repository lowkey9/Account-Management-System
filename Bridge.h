/*
* Declaration of class Bridge
* disign pattern
*/

#include <iostream>
#include "Account.h"
#include "BankAccount.h"
#include "StockAccount.h"

#ifndef ACCOUNTINTERFACE
#define ACCOUNTINTERFACE 

class AccountInterface {
public:
	AccountInterface()
	{
		imp = new Account;
	}
	Account * imp;
};

#endif

#ifndef BANKACCOUNTINTERFACE
#define BANKACCOUNTINTERFACE

class BankAccountInterface :public AccountInterface
{
public:
	BankAccountInterface()
	{
		imp = new BankAccount;
	}
};

#endif

#ifndef STOCKACCOUNTINTERFACE
#define STOCKACCOUNTINTERFACE

class StockAccountInterface :public AccountInterface
{
public:
	StockAccountInterface()
	{
		imp = new StockAccount;
	}
};

#endif