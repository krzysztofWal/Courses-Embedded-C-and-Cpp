#include "Account.h"

Account::Account(std::string name, double balance) 
    : name{name}, balance{balance} {
        if (balance < 0.0)
            throw IllegalBalanceException();
}

bool Account::deposit(double amount) {
    if (amount < 0) 
        return false;
    else {
        balance += amount;
        return true;
    }
}

void Account::withdraw(double amount) {
    if (balance-amount >=0) {
        balance-=amount;
    } else
        throw InsufficientFundsException();
}

 void Account::print(std::ostream &os) const {
    os.precision(2);
    os << std::fixed;
    os << "[Account: " << name << ": " << balance << "]";
}
