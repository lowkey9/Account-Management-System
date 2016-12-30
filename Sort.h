/*
* Declaration of class Sort*
* used to sort the stock portfolio list
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include "StockAccount.h"

#ifndef SORTIMP
#define SORTIMP

class SortImp {
public:
	virtual void sort(StockAccount *) = 0;
};
#endif

#ifndef SORTBUBBLE
#define SORTBUBBLE

class SortBubble :public SortImp {
public:
	virtual void sort(StockAccount *);

};
#endif

#ifndef SORTSELECTION
#define SORTSELECTION

class SortSelection :public SortImp {
public:
	virtual void sort(StockAccount *);
};
#endif

#ifndef STAT
#define STAT

class Stat {
public:
	void bubble() { imp = new SortBubble; }
	void selection() { imp = new SortSelection; }
	void dosort(StockAccount *list) { imp->sort(list); }
private:
	SortImp * imp;
};
#endif