/*
* Declaration of class StockAccount
* derived class of base class Account
* friend class of PortfolioNode
*/

#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H
#include <string>
#include "Account.h"
#include "PortfolioNode.h"

using namespace std;

class StockAccount :public Account
{
	friend class SortBubble;
	friend class SortSelection;
	friend class Sort;
	friend class Stat;
private:
	PortfolioNode *stockHead;
	PortfolioNode *stockTail;
	int stockSize;
public:
	StockAccount();
	~StockAccount();
	virtual void buyshare();
	virtual void sellshare();
	virtual void viewCurS(int);
	virtual void graph();
	virtual void viewSTHist();
	virtual PortfolioNode* search(string);
	virtual void addStock(PortfolioNode *);
	virtual void deleteStock(PortfolioNode *);
	virtual void storeStock();
	virtual bool loadStock();
	virtual double getRandPrice(string&);
	virtual void sortportfolio(int);
};

#endif