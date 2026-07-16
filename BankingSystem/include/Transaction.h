#ifndef TRANSACTION_H
#define TRANSACTION_H

class Transaction {
	public:
		static const int DEPOSIT = 0;
		static const int TRANSFER = 1;
		static const int WITHDRAWAL = 2;
		
		int type;
		int dollars;
		unsigned int account_number;
		unsigned int to_acct;

		Transaction(int t, int d, unsigned int acc, unsigned int to = 0);

};

#endif
