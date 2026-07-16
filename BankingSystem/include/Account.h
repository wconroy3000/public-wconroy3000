#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>


class Account {
public:

    Account();

    Account(std::string ownerName, int openedYear,std::string accN, std::string accT, unsigned int money );
    Account(std::string ownerName, int openedYear, int accNumber, std::string accT, unsigned int balance);

    std::string getAccountNumber();
    int getYearOpened() const; 
    void display() const;

    unsigned int getBalance() const;
    void deposit(int amt);
    void withdraw(int amt);

private:
    std::string owner;
    std::string acc_number;
    int yearOpened;
    unsigned int bal;
    std::string acct;
	
};

#endif

