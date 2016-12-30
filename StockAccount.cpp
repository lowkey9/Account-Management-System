/*
* member functions of class StockAccount
*/
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include <engine.h>

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include "StockAccount.h"
#include "Sort.h"

#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )
#pragma comment( lib, "libeng.lib" )

using namespace std;

StockAccount::StockAccount() :stockHead(0), stockTail(0), stockSize(0)
{}

StockAccount::~StockAccount()
{
	//delete double linked list used to store information of user's stock
	if (!stockSize)
	{
		cout << "Destroying portfolio list ...\n";
		PortfolioNode *currentPtr = stockHead;
		PortfolioNode *tmpPrt;
		while (currentPtr != 0) {
			tmpPrt = currentPtr;
			currentPtr = currentPtr->next;
			delete tmpPrt;
			stockSize--;
		}
	}
	cout << "Portfolio list destroied.\n";
}

double StockAccount::getRandPrice(string& name)
{
	srand(time(NULL));
	int randnum = rand() % 2;
	int i = 0;

	string str;
	string delimeter = "\t";
	string::size_type start = 0, index;
	string substr;
	string name_;
	double amount_;
	int counter = 0;

	string *symbol = new string;
	double *price = new double;
	string *date = new string;
	if (randnum == 0)
	{
		ifstream ifile;
		ifile.open("Result_1.txt");
		if (!ifile)
		{
			cout << "Cannot open file.\n";
			return 0;
		}
		while (!ifile.eof())
		{
			getline(ifile, str);
			index = str.find_first_of(delimeter, start);
			while (index != string::npos) {
				substr = str.substr(start, index - start);
				if (counter % 2 == 0)
					name_ = substr;
				else
					amount_ = atoi(substr.c_str());
				counter++;
				start = str.find_first_not_of(delimeter, index);
				if (start == string::npos)
					break;
				index = str.find_first_of(delimeter, start);
			}
			start = 0;

			symbol[i] = name_;
			price[i] = amount_;
			i++;
		}
		ifile.close();
	}
	else
	{
		ifstream ifile;
		ifile.open("Result_2.txt");
		if (!ifile)
		{
			cout << "Cannot open file.\n";
			return 0;
		}
		{
			getline(ifile, str);
			index = str.find_first_of(delimeter, start);
			while (index != string::npos) {
				substr = str.substr(start, index - start);
				if (counter % 2 == 0)
					name_ = substr;
				else
					amount_ = atof(substr.c_str());
				counter++;
				start = str.find_first_not_of(delimeter, index);
				if (start == string::npos)
					break;
				index = str.find_first_of(delimeter, start);
			}
			start = 0;

			symbol[i] = name_;
			price[i] = amount_;
			i++;
		}
		ifile.close();
	}
	for (int j = 0; j < i+1; j++)
	{
		if (name == symbol[j]) {
			//cout << price[j];
			return price[j];
		}
	}
	return 0;
}

PortfolioNode* StockAccount::search(string name)
{
	PortfolioNode *currentPtr = stockHead;
	PortfolioNode *tmpPtr;
	bool flag = false;
	if (currentPtr == NULL)
		flag = false;
	if (currentPtr->stockName == name) {
		tmpPtr = currentPtr;
		flag = true;
	}
	else {
		while (1) {
			if (currentPtr->next != NULL) {
				if (currentPtr->next->stockName == name) {
					tmpPtr = currentPtr->next;
					flag = true;
					break;
				}
				currentPtr = currentPtr->next;
			}
			else {
				if (currentPtr->stockName == name) {
					tmpPtr = currentPtr;
					flag = true;
					break;
				}
				break;
			}
		}
	}
	if (!flag) {
		return NULL;
	}
	else {
		return tmpPtr;
	}
}

void StockAccount::addStock(PortfolioNode *newStock)
{
	if (!stockSize) {
		stockHead = stockTail = newStock;
	}
	else {
		stockTail->next = newStock;
		stockTail = newStock;
	}
	stockSize++;
}

void StockAccount::deleteStock(PortfolioNode *oldStock)
{
	PortfolioNode *tmpPtr = NULL;
	/*if this node is the 1st one*/
	if (oldStock == stockHead) {
		tmpPtr = oldStock;
		oldStock->next->last = NULL;
		stockHead = stockHead->next;
		delete tmpPtr;
	}
	/*if thsi node is the last one*/
	else if (oldStock == stockTail) {
		tmpPtr = oldStock;
		oldStock->last->next = NULL;
		stockTail = stockTail->last;
		delete tmpPtr;
	}
	else {
		tmpPtr = oldStock;
		oldStock->last->next = oldStock->next;
		oldStock->next->last = oldStock->last;
		delete tmpPtr;
	}
	stockSize--;
	return;
}

void StockAccount::buyshare()
{
	PortfolioNode *tmp = NULL;
	string symbol;
	int NumofShares = 0;
	double MaxValue = 0.0;
	/*print out instructions on screen, get user's input*/
	cout << "Please enter the stock symbol you wish to purchase: ";
	cin >> symbol;
	transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
	cout << "Please enter the number of shares: ";
	cin >> NumofShares;
	cout << "Please enter the maximum amount you are willing to pay per share: ";
	cin >> MaxValue;

	double price = 0.0;
	price = getRandPrice(symbol);		//get price randomly
	cout << "Got price\n";
	/*return if stock symbol mismatch*/
	if (price == 0) {
		cout << "Stock not found or file cannot be opened.\n";
		return;
	}
	else {
		/*return if price per share is higher than what user wants to pay*/
		if (price > MaxValue) {
			cout << "The price per share of this stock is higher than that you want to pay.\nTransaction Failed!\n";
			return;
		}

		/*return if user's cash balance is not enough*/
		if (price*NumofShares > getBalance()) {
			cout << "Your cash balance is not enough.\nTransaction Failed!\n";
			return;
		}

		/*transaction goes through*/
		
		CashBalance -= NumofShares*price;		//deducte cost from cash balance
		cout << "Set Cash Balance\n";

		/*operations when user already has this stock*/
		PortfolioNode *tmpStock;
		tmpStock = search(symbol);
		cout << "Found stock\n";
		//if user does not have this stock
		if (!tmpStock) {
			tmpStock = new PortfolioNode(symbol, price, NumofShares);
			addStock(tmpStock);
			cout << "stock added\n";
		}
		else {
			tmpStock->stockNum += NumofShares;
			tmpStock->stockPrice = price;
			tmpStock->stockValue = tmpStock->stockNum * tmpStock->stockPrice;
			cout << "stock info changed\n";
		}

		/*record transaction history*/
		time_t seconds;
		tm *timeinfo;
		ofstream ofile1, ofile2;
		//stock transaction history
		ofile1.open("stock_transaction_history.txt", ios::app);
		seconds = time(NULL);
		timeinfo = localtime(&seconds);
		ofile1 << "BUY\t" << symbol << "\t" << NumofShares << "\t" << price << "\t" << NumofShares*price << "\t" << asctime(timeinfo) << endl;
		ofile1.close();
		//bank transaction history
		ofile2.open("bank_transaction_history.txt", ios::app);
		ofile2 << "WITHDRAW\t" << NumofShares*price << "\t" << asctime(timeinfo) << "\t" << getBalance() << endl;
		ofile2.close();

		cout << "You have purchased " << NumofShares << "shares of " << symbol << "at $" << price << "each for a total of $" << NumofShares*price;
	}
}

void StockAccount::sellshare()
{
	PortfolioNode *tmp = NULL;
	string symbol;
	int NumofShares = 0;
	double MinValue = 0.0;
	/*print out instructions on screen, get user's input*/
	cout << "Please enter the stock symbol you wish to sell: ";
	cin >> symbol;
	transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
	cout << "Please enter the number of shares: ";
	cin >> NumofShares;
	cout << "Please enter the mniimum amount you are willing to sell per share: ";
	cin >> MinValue;

	double price = 0.0;
	price = getRandPrice(symbol);		//get price randomly

	/*return if stock symbol mismatch*/
	PortfolioNode *tmpStock;
	if (price == 0) {
		cout << "Stock not found or file cannot be opened.\n";
		return;
	}
	else if (!(tmpStock = search(symbol))) {
		cout << "You don't have this stock.\n";
		return;
	}
	else {
		/*return if price per share is higher than what use wants to pay*/
		if (price < MinValue) {
			cout << "The price per share of this stock is lower than that you want to sell.\nTransaction Failed!\n";
			return;
		}

		/*return if user's cash balance is not enough*/
		if (NumofShares > tmpStock->stockNum) {
			cout << "there are insufficient shares in the portfolio.\nTransaction Failed!\n";
			return;
		}

		/*transaction goes through*/
		CashBalance += NumofShares*price;			//add income to cash balance
		tmpStock->stockNum -= NumofShares;			//change info stored in portfolio

		/*delete portfolio node if it's #shares is 0*/
		if (tmpStock->stockNum == 0)
			this->deleteStock(tmpStock);
		else
			tmpStock->stockValue = tmpStock->stockNum * tmpStock->stockPrice;

		/*record transaction history*/
		time_t seconds;
		tm *timeinfo;
		ofstream ofile1, ofile2;
		//stock transaction history
		ofile1.open("stock_transaction_history.txt", ios::app);
		seconds = time(NULL);
		timeinfo = localtime(&seconds);
		ofile1 << "SELL\t" << symbol << "\t" << NumofShares << "\t" << price << "\t" << NumofShares*price << "\t" << asctime(timeinfo) << endl;
		ofile1.close();
		//bank transaction history
		ofile2.open("bank_transaction_history.txt", ios::app);
		ofile2 << "DEPOSIT\t" << NumofShares*price << "\t" << asctime(timeinfo) << "\t" << getBalance() << endl;
		ofile2.close();

		cout << "You have sold " << NumofShares << "shares of " << symbol << "at $" << price << "each for a total of $" << NumofShares*price;
	}
}

void StockAccount::viewCurS(int choice)
{
	sortportfolio(choice);

	/*display current cash balance*/
	double balance = getBalance();
	cout << "Cash balance = $" << balance << endl;
	cout << "CompanySymbol" << setw(11) << "Number" << setw(18) << "PricePerShare" << setw(15) << "TotalValue\n";
	
	/*display current stock list*/
	PortfolioNode *currentPtr = stockHead;
	PortfolioNode *tmp = NULL;
	double myPrice = 0.0;
	double totalPVal = 0.0;
	for (int i = 0; i < stockSize; i++) {
		myPrice = getRandPrice(currentPtr->stockName);
		currentPtr->stockValue = currentPtr->stockNum * myPrice;
		cout << currentPtr->stockName << "\t" << currentPtr->stockNum << "\t" << myPrice << "\t" << currentPtr->stockValue << endl;
		totalPVal += currentPtr->stockValue;
		if (currentPtr->next != NULL)
			currentPtr = currentPtr->next;
	}

	/*display current total portfolio value*/
	cout << "Total portfolio value: $" << totalPVal << endl;
}

void StockAccount::viewSTHist()
{
	string str;
	ifstream ifile;
	ifile.open("stock_transaction_history.txt");
	cout << endl;
	while (!ifile.eof()) {
		getline(ifile, str);
		cout << str << endl;
	}
	ifile.close();
}

void StockAccount::storeStock()
{
	ofstream ofile;
	ofile.open("stock_hist.txt");

	PortfolioNode *curPtr = stockHead;
	for (int i = 0; i < stockSize; i++)
	{
		ofile << curPtr->stockName << "\t" << curPtr->stockNum << endl;
		curPtr = curPtr->next;
	}

	ofile.close();
}

bool StockAccount::loadStock()
{
	bool flag = true;

	ifstream ifile;
	ifile.open("stock_hist.txt");

	if (!ifile) {
		cout << "Cannot open file.\n";
		flag = false;
		return flag;
	}

	if (ifile.eof()) {
		flag = false;
		return flag;
	}

	string name_;
	int num_ = 0;
	double price_ = 0.0;
	PortfolioNode *newStock;
	PortfolioNode *tmp = NULL;
	while (!ifile.eof())
	{
		ifile >> name_ >> num_;
		price_ = getRandPrice(name_);
		newStock = new PortfolioNode(name_, price_, num_);
		addStock(newStock);
		stockSize++;
	}

	return flag;
}

void StockAccount::sortportfolio(int choice)
{
	Stat sort;
	if (choice == 1)
	{
		sort.bubble();
		sort.dosort(this);
	}
	else {
		sort.selection();
		sort.dosort(this);
	}
}

void StockAccount::graph()
{
	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		cout << "Error: Not Found" << endl;
		exit(1);
	}

	double *totalVal = new double;
	int counter = 0;
	double *size = new double;
	PortfolioNode *temp = this->stockHead;

	while (temp != NULL)
	{
		double price1 = getRandPrice(temp->stockName); //since the price of the stock will be used twice here, so use "price1" to prevent the price from changing.
		totalVal[counter] += temp->stockNum * price1;
		size[counter] = counter;
		cout << totalVal[counter] << "\t" << size[counter] << endl;
		counter++;
		//cout << left << setw(16) << temp->symbol << setw(9) << temp->share << setw(16) << price1 << temp->share * price1 << endl;
		temp = temp->next;
	}
	mxArray *m_Val, *m_Size;
	m_Val = mxCreateDoubleMatrix(1, counter + 1, mxREAL);
	m_Size = mxCreateDoubleMatrix(1, counter + 1, mxREAL);
	memcpy((void*)mxGetPr(m_Val), (void*)totalVal, (counter + 1)*sizeof(double));
	memcpy((void*)mxGetPr(m_Size), (void*)size, (counter + 1)*sizeof(double));

	engPutVariable(ep, "totalVal", m_Val);
	engPutVariable(ep, "size", m_Size);

	engEvalString(ep, "plot(size,totalVal)");
}