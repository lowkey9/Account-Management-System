/*
* Declaration of class Account
* base class
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "PortfolioNode.h"
class Account
{
public:
	void setBalance();
	//void changeBalance(double);
	void storeBalance();
	bool loadBalance();
	double getBalance() const;

	//vitrual function for BankAccount
	virtual void deposit() { return; };
	virtual void withdraw() { return; };
	virtual void viewBTHist() { return; };

	//virtual functoin for StockAccount
	virtual void buyshare() { return; };
	virtual void sellshare() { return; };
	virtual void viewCurS(int) { return; };
	virtual void graph() { return; };
	virtual void viewSTHist() { return; };
	virtual PortfolioNode* search(string) { PortfolioNode *node = NULL; return node; };
	virtual void addStock(PortfolioNode *) { return; };
	virtual void deleteStock(PortfolioNode *) { return; };
	virtual void storeStock() { return; };
	virtual bool loadStock() { return false; };
	virtual double getRandPrice(string&) { return 0.0; };
	virtual void sortportfolio(int) { return; };

protected:
	double CashBalance;
};

#endif
