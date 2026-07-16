#ifndef BANKVAULT_H
#define BANKVAULT_H
#include <string>
#include "Account.h"
#include "TransactionList.h"

class TransactionList;

class BankVault {
public:

	BankVault(unsigned int initial_capacity);
	BankVault();

	BankVault(const BankVault& c);
	~BankVault();
	BankVault& operator=(const BankVault& rhs);
	
	bool addAccount(Account& acct);
	bool removeAccount(const std::string& acc_number);
	Account findAccount(const std::string& acc_number);
	Account findAccount(unsigned int _number);

	void getSizes(unsigned int &count, unsigned int &capacity, bool verbose=false); 
	void display(int year = 2026) const;

	bool applyTransactions(TransactionList& list);


private:
	unsigned int numAccounts;
	unsigned int capacity;
	Account* accPtr = nullptr;
};

#endif
