/*
* member functions of class Sort*
*/

#include <iostream>

#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include "StockAccount.h"
#include "Account.h"
#include "Sort.h"

//Bubble sort
void SortBubble::sort(StockAccount * list)
{
	PortfolioNode *curPtr = list->stockHead;
	if (curPtr == NULL) //if there is no Node, there is no need to Sort
		return;
	if (curPtr->next == NULL)  //If there is only one Node, there is no need to Sort
		return;
	PortfolioNode * q = list->stockHead->next;
	int share;
	string symbol;
	int m = 0;
	int n = 0;
	int size = list->stockSize;
	while (m < size - 1)
	{
		n = 0;
		while (n < size - 1 - m)
		{
			if ((q->stockPrice * q->stockNum) >(curPtr->stockPrice * curPtr->stockNum))
			{
				share = q->stockNum;
				q->stockNum = curPtr->stockNum;
				curPtr->stockNum = share;
				symbol = q->stockName;
				q->stockName = curPtr->stockName;
				curPtr->stockName = symbol;
			}
			curPtr = curPtr->next;
			q = q->next;
			n++;
		}
		curPtr = list->stockHead;
		q = list->stockHead->next;
		m++;
	}
}

//Selection sort
void SortSelection::sort(StockAccount * list)
{
	PortfolioNode *curPtr = list->stockHead;
	if (curPtr == NULL) //if there is no Node, there is no need to Sort
		return;
	if (curPtr->next == NULL)  //If there is only one Node, there is no need to Sort
		return;
	PortfolioNode * q = list->stockHead->next;
	int share;
	string symbol;
	int m = 0;
	int n = 0;
	int size = list->stockSize;
	while (m < size - 1)
	{
		n = 0;
		q = curPtr->next;
		while (n < size - 1 - m)
		{

			if ((q->stockPrice * q->stockNum) >(curPtr->stockPrice * curPtr->stockNum))
			{
				share = q->stockNum;
				q->stockNum = curPtr->stockNum;
				curPtr->stockNum = share;
				symbol = q->stockName;
				q->stockName = curPtr->stockName;
				curPtr->stockName = symbol;
			}
			q = q->next;
			n++;
		}
		curPtr = curPtr->next;
		m++;
	}
}