#include <Trust_Account.h>

Trust_Account::Trust_Account(std::string name, double amount, double int_rate)
 : Savings_Account{name, amount, int_rate}, count {0} {
 }
 
 bool Trust_Account::deposit(double amount) {
	 double new_amount = amount + amount*int_rate/100;
	 if (amount >= bonus_threshold) new_amount += bonus_amount;
	 return Account::deposit(new_amount);
 }
 
 bool Trust_Account::withdraw(double amount) {
	count++;
	if (count <= max_withdrawals && amount <= max_withdraw_percent * balance) return Account::withdraw(amount);
	else return false;
 }
 
 int Trust_Account::get_count() const {
	 return count;
 }
 
 std::ostream &operator<<(std::ostream &os, const Trust_Account &account) {
    os << "[Trust_Account: " << account.name << ": " << account.balance << ", " << account.int_rate << "%]";
    return os;
}