#include <iostream>
#include "Account_Util.h"

void display(const std::vector<Account *> &accounts) {
    std::cout << "\n=== Checking Accounts=====================================" << std::endl;
    for (const auto acc: accounts) 
        std::cout << *acc;
}

void deposit(std::vector<Account *> &accounts, double amount) {
    std::cout << "\n=== Depositing to Checking Accounts===========================" << std::endl;
    for (auto acc:accounts)  {
        if (acc->deposit(amount)) 
            std::cout << "Deposited " << amount << " to " << *acc ;
        else
            std::cout << "Failed Deposit of " << amount << " to " << *acc;
    }
}

void withdraw(std::vector<Account *> &accounts, double amount) {
    std::cout << "\n=== Withdrawing from Checking Accounts=======================" << std::endl;
    for (auto acc:accounts)  {
        if (acc->withdraw(amount)) 
            std::cout << "Withdrew " << amount << " from " << *acc ;
        else
            std::cout << "Failed Withdrawal of " << amount << " from " << *acc ;
    } 
}