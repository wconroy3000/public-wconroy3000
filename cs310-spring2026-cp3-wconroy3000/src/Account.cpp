#include <iostream>
#include <string>
#include "Account.h"


Account::Account() {
	owner = "";
	yearOpened = 0;
	acc_number = "";
	acct = "";
	bal = 0;
}


Account::Account(std::string ownerName, int openedYear, std::string accNumber, std::string accT, unsigned int balance) {
	owner = ownerName;
	yearOpened = openedYear;
	acc_number = accNumber;
	acct = accT;
	bal = balance;
}	

Account::Account(std::string ownerName, int openedYear, int accNumber, std::string accT, unsigned int balance) {
    owner = ownerName;
    yearOpened = openedYear;
    acc_number = std::to_string(accNumber);
    acct = accT;
    bal = balance;
}

void Account::display() const {
	std::cout << owner << " [" << yearOpened << "] " << acc_number << " " << acct << " $" << bal << std::endl;
}

std::string Account::getAccountNumber() {
	return acc_number;
}


int Account::getYearOpened() const {
	return yearOpened;
}


unsigned int Account::getBalance() const {
    return bal;
}



void Account::deposit(int amt) {
	bal += amt;
}

void Account::withdraw(int amt) {
	bal -= amt;
}
