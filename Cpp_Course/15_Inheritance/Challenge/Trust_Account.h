#ifndef _TRUST_ACCOUNT_H_
#define _TRUST_ACCOUNT_H_
#include "Savings_Account.h"

class Trust_Account: public Savings_Account {
	friend std::ostream &operator<<(std::ostream &os, const Trust_Account &account);
private:
	static constexpr const char *def_name = "Unnamed Trust Account";
	static constexpr double def_amount = 0.0;
	static constexpr double def_int_rate = 0.0;
	static constexpr double bonus_amount = 50.0;
	static constexpr double bonus_threshold = 5000.0;
	static constexpr double max_withdraw_percent = 0.2;
	static constexpr int  max_withdrawals = 3;
protected:
	int count;
public:
	Trust_Account(std::string name = def_name, double amount = def_amount, double int_rate = def_int_rate);
	bool deposit(double amount);
	bool withdraw(double amount);
	int get_count() const; 
};
#endif