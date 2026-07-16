#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H
#include <string>
#include <ostream>
#include "Transaction.h"

class BankVault;

class TransactionList {
private:
	class Node {
	public:
		Transaction data;
		Node* next;
		Node* prev;

		Node(Transaction t) : data(t) {
			next = prev = nullptr;
		}
	};
	Node *head, *tail;
	int size;	


public:
	int length() const;
	bool deposit(int dollars, unsigned int account_number);
	bool withdraw(int dollars, unsigned int account_number);
	bool transfer(int dollars, unsigned int from_acct, unsigned int to_acct);
		
	int collapse();
	int sort(std::string key = "account_number");

	TransactionList();
	TransactionList& operator+=(TransactionList& other);
	~TransactionList(); 
	TransactionList& operator=(const TransactionList& other);
	TransactionList(const TransactionList& other);

	friend std::ostream& operator<<(std::ostream& os, const TransactionList& list);

	Transaction* getFirst();
	Transaction* getNext(Transaction* curr);
	bool remove(Transaction* t);

};

#endif
	
