/*
* main function
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "Account.h"
#include "BankAccount.h"
#include "StockAccount.h"
#include "Sort.h"
#include "Bridge.h"
#include "PortfolioNode.h"

using namespace std;

int main()
{
	cout << "Welcome to the Account Management System" << endl;
	cout << "********Initializing********\n";
	AccountInterface *myAccount = new AccountInterface;
	AccountInterface *bankAccount = new BankAccountInterface;
	AccountInterface *stockAccount = new StockAccountInterface;
	//BankAccount bankAccount;

	/*flag indicates whether loading file succeed*/
	//bool flag = bankAccount.loadBalance();
	
	cout << "****Initialization Done****\n";
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!have not init stockAccount!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	
	/*choose sorting method*/
	int sortchoice;
	cout << "Please choose which sorting method you want to use\n1 for Bubble Sort\n2 stands for Selection Sort\n";
	cin >> sortchoice;

	double myBalance = 0.0;
	double myPrice = 0.0;
	string mySymbol;
	int choice = 0;
	int subchoice = 0;
	/*
	while (subchoice != 5) {
		cout << "\n**********Bank Portfolio Account**********\n";
		cout << "Please select an option:\n";
		cout << "1. View account balance\n";
		cout << "2. Deposit money\n";
		cout << "3. Withdraw money\n";
		cout << "4. Print out history\n";
		cout << "5. Return to previous menu\n";

		cin >> subchoice;

		switch (subchoice)
		{
		case 1:
			myBalance = bankAccount->imp->getBalance();
			cout << myBalance << endl;
			break;
		case 2:
			bankAccount->imp->deposit();
			break;
		case 3:
			bankAccount->imp->withdraw();
			break;
		case 4:
			bankAccount->imp->viewBTHist();
			break;
		default:
			break;
		}
	}

	bankAccount->imp->storeBalance();

	return 0;
	*/

	while (choice != 3) {

		cout << "1. Stock Portfolio Account\n";
		cout << "2. Bank Account\n";
		cout << "3. Exit\n";
		cout << "Please select an account to access:\n";

		cin >> choice;

		switch (choice)
		{
		case 1:
			stockAccount->imp->loadBalance();
			cout << "stock load cash balance\n";
			if (stockAccount->imp->getBalance() <= 0) {
				cout << "no history in file, set cash balance to 10000.\n";
				stockAccount->imp->setBalance();
			}
			subchoice = 0;
			while (subchoice != 7) {
				cout << "\n**********Stock Portfolio Account**********\n";
				cout << "Please select an option:\n";
				cout << "1. Display the price for a stock symbol\n";
				cout << "2. Display the current portfolio\n";
				cout << "3. Buy shares\n";
				cout << "4. Sell shares\n";
				cout << "5. View a graph for the portfolio value\n";
				cout << "6. View transaction history\n";
				cout << "7. Return to previous menu\n";

				cin >> subchoice;

				switch (subchoice)
				{
				case 1:
					cout << "Please input the stock symbol: ";
					cin >> mySymbol;
					transform(mySymbol.begin(), mySymbol.end(), mySymbol.begin(), ::toupper);
					myPrice = stockAccount->imp->getRandPrice(mySymbol);
					cout << "Price per share: " << myPrice << endl;
					break;
				case 2:
					stockAccount->imp->viewCurS(sortchoice);
					break;
				case 3:
					stockAccount->imp->buyshare();
					break;
				case 4:
					stockAccount->imp->sellshare();
					break;
				case 5:
					stockAccount->imp->graph();
					break;
				case 6:
					stockAccount->imp->viewSTHist();
					break;
				default:
					//cout << "Invalid!\nPlease enter again\n";
					break;
				}
			}
			break;
		case 2:
			bankAccount->imp->loadBalance();
			if (bankAccount->imp->getBalance() <= 0) {
				cout << "no history in file, set case balance to 10000.\n";
				bankAccount->imp->setBalance();
			}
			subchoice = 0;
			while (subchoice != 5) {
				cout << "\n**********Bank Portfolio Account**********\n";
				cout << "Please select an option:\n";
				cout << "1. View account balance\n";
				cout << "2. Deposit money\n";
				cout << "3. Withdraw money\n";
				cout << "4. Print out history\n";
				cout << "5. Return to previous menu\n";

				cin >> subchoice;

				switch (subchoice)
				{
				case 1:
					myBalance = bankAccount->imp->getBalance();
					cout << myBalance << endl;
					break;
				case 2:
					bankAccount->imp->deposit();
					break;
				case 3:
					bankAccount->imp->withdraw();
					break;
				case 4:
					bankAccount->imp->viewBTHist();
					break;
				default:
					break;
				}
			}
			break;
		default:
			//cout << "Invalid!\nPlease enter again\n";
			break;
		}
	}

	bankAccount->imp->storeBalance();
	stockAccount->imp->storeStock();

	return 0;
}