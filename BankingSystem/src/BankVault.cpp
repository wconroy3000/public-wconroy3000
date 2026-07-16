#include <iostream>
#include "BankVault.h"
#include "Account.h"
#include "TransactionList.h"
#include <string>

BankVault::BankVault() {
	capacity = 1;
	numAccounts = 0;
	accPtr = new Account[capacity];
}
	


BankVault::BankVault(unsigned int initial_capacity) {
	if (initial_capacity>0) {
		capacity = initial_capacity;
	}
	else {
		capacity = 1;
	}
	numAccounts = 0;
	accPtr = new Account[capacity];
}


BankVault::BankVault(const BankVault& c) {
	this->capacity = c.capacity;
	this->numAccounts = c.numAccounts;

	this->accPtr = new Account[this->capacity];
	for(unsigned int i = 0; i < numAccounts; i++) {
		this->accPtr[i] = c.accPtr[i];
	}
}



BankVault::~BankVault() {
	delete[] accPtr;
}



BankVault& BankVault::operator=(const BankVault& rhs) {
	if (this == &rhs) return *this;
	
	this->capacity = rhs.capacity;
	this->numAccounts = rhs.numAccounts;

	delete[] accPtr;
	this->accPtr = new Account[this->capacity];
	for (unsigned int i = 0; i < numAccounts; i++) {
		this->accPtr[i] = rhs.accPtr[i];
	}
	return *this;
}



void BankVault::display(int year) const {
	std::cout << "Number of accounts: " << numAccounts << " " << std::endl;
	for (unsigned int i =0; i < numAccounts; i++) {
		if(accPtr[i].getYearOpened() < year) {
			accPtr[i].display();
		}
	}
};

bool BankVault::addAccount(Account& acct) {
	if (numAccounts >= capacity)	{
		capacity *= 2;
		Account *newArr = new Account[capacity];
		for (unsigned int i =0; i < numAccounts; i++) {
			newArr[i] = accPtr[i];
		}
		delete[] accPtr;
		accPtr = newArr;

	}
	accPtr[numAccounts] = acct;
	numAccounts++;
	return true;


};

bool BankVault::removeAccount(const std::string& acc_number) {
	for (unsigned int i =0; i < numAccounts; i++) {
		if (accPtr[i].getAccountNumber() == acc_number) {
			for (unsigned int j = i;j < numAccounts - 1; j++) {
				accPtr[j] = accPtr[j+1];
			}
			numAccounts--;
			if (numAccounts * 2 <= capacity) {
				unsigned int shrink = (capacity + 3) / 4;
				capacity = capacity - shrink;
				Account* newArr = new Account[capacity];
				for (unsigned int i =0; i < numAccounts; i++) {
					newArr[i] = accPtr[i];
				}
				delete[] accPtr;
				accPtr = newArr;
			}


			return true;
		}
	}
	std::cout << "Account not found." << std::endl;
	return false;
}


Account BankVault::findAccount(const std::string& acc_number) {
	for (unsigned int i = 0; i < numAccounts; i++) {
		if (accPtr[i].getAccountNumber() == acc_number) {
			return accPtr[i];
		}
	}
	Account a; 
	return a;
}

Account BankVault::findAccount(unsigned int acc_number) {
    return findAccount(std::to_string(acc_number));
}

void BankVault::getSizes(unsigned int &count, unsigned int &capacity, bool verbose) {
	count = numAccounts;
	capacity = this->capacity;
	
	if (verbose == true) {
		std::cout << "Elements: " << count << " Capacity: " << capacity << std::endl;
	}
}



bool BankVault::applyTransactions(TransactionList& list) {
        Transaction* curr = list.getFirst();
        bool applied = false;

        while (curr != nullptr) {
                Transaction* next = list.getNext(curr);
                bool success = false;

                Account* fromAcc = nullptr;
                Account* toAcc = nullptr;

                for (unsigned int i = 0; i < numAccounts; i++) {
                        if (accPtr[i].getAccountNumber() == std::to_string(curr->account_number)) {
                                fromAcc = &accPtr[i];
                                break;
                        }
                }

                if (curr->type == Transaction::DEPOSIT) {
                        if (fromAcc) {
                                fromAcc->deposit(curr->dollars);
                                success = true;
                        }
                }
                else if (curr->type == Transaction::WITHDRAWAL) {
                        if (fromAcc) {
                                fromAcc->withdraw(curr->dollars);
                                success = true;
                        }
                }
                else if (curr->type == Transaction::TRANSFER) {
                        for (unsigned int i = 0; i < numAccounts; i++) {
                                if (accPtr[i].getAccountNumber() == std::to_string(curr->to_acct)) {
                                        toAcc = &accPtr[i];
                                        break;
                                }
                        }

                        if (fromAcc && toAcc) {
                                fromAcc->withdraw(curr->dollars);
                                toAcc->deposit(curr->dollars);
                                success = true;
                        }
                }

                if (success) {
                        list.remove(curr);
                        applied = true;
                }

                curr = next;
        }

        return applied;
}



