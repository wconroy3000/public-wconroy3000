#include "Transaction.h"
	
	
Transaction::Transaction(int t, int d, unsigned int acc, unsigned int to) {
	type = t;
	dollars = d;
	account_number = acc;
	to_acct = to;
}
