/*
* Declaration of class PortfolioNode
* node in double linked list
* store information of user's stock
*/

#ifndef PORTFOLIONODE_H
#define PORTFOLIONODE_H
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

class PortfolioNode
{
	friend class StockAccount;
	friend class SortBubble;
	friend class SortSelection;
	friend class Sort;
	friend class Stat;
private:
	string stockName;
	double stockPrice;
	int stockNum;
	double stockValue;
	PortfolioNode *last;
	PortfolioNode *next;
public:
	PortfolioNode(string& name, double price, int amount) :stockName(name), stockPrice(price), stockNum(amount)
	{
		last = NULL;
		next = NULL;
		stockValue += stockNum * stockPrice;
	}
	//double getRandPrice(string&);
};
/*
double PortfolioNode::getRandPrice(string& name)
{
	srand(time(NULL));
	int randnum = rand() % 2;
	int i = 0;

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
		while (ifile >> symbol[i] >> price[i] >> date[i])
			i++;
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
		while (ifile >> symbol[i] >> price[i] >> date[i])
			i++;
		ifile.close();
	}
	for (int j = 0; j < i + 1; j++)
	{
		if (name == symbol[j])
			return price[j];
	}
	return 0;
}
*/
#endif
