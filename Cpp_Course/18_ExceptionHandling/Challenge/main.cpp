#include <iostream>
#include <memory>
#include "Account.h"
#include "Checking_Account.h"
#include "Savings_Account.h"
#include "Trust_Account.h"
#include "Account_Util.h"

using namespace std;

int main() {
    // test your code here
	try {
	std::unique_ptr<Checking_Account> ptr = std::make_unique<Checking_Account>("Alice", -12);
    } catch (const IllegalBalanceException  &ex) {
		std::cout << ex.what() << std::endl;
	}
	
	std::unique_ptr<Savings_Account> ptr2 = std::make_unique<Savings_Account>("Captain",20, 1.5);
	std::cout << *ptr2 << std::endl;
	try {
		ptr2 -> withdraw(1000);
	} catch (const InsufficientFundsException &ex) {
		std::cout << ex.what() << std::endl;
	}
	
    std::cout << "Program completed successfully" << std::endl;
	
	return 0;
}

