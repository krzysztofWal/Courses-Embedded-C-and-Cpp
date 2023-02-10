#include "Checking_Account.h"

Checking_Account::Checking_Account(std::string name, double balance)
    : Account {name, balance} {
}

bool Checking_Account::withdraw(double amount) {
    amount += per_check_fee;
    return Account::withdraw(amount);
}

bool Checking_Account::deposit(double amount) {
	return Account::deposit(amount); 
//	std::cout <<  "Checking_Account deposit";
}

void Checking_Account::print(std::ostream &os) const {
//	os << this->name;
	os << "[Checking_Account: " << this->name << ": " << this->balance  << "]";
}

//
//std::ostream &operator<<(std::ostream &os, const Checking_Account &account) {
//    os << "[Checking_Account: " << account.name << ": " << account.balance  << "]";
//    return os;
// }

