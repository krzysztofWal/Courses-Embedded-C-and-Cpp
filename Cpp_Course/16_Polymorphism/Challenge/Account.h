// Simple Account 
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include <iostream>
#include <string>
#include "I_Printable.h"

class Account: public I_Printable {
//    friend std::ostream &operator<<(std::ostream &os, const Account &account);
private:   
    static constexpr const char *def_name = "Unnamed Account";
    static constexpr double def_balance = 0.0;
protected:
    std::string name;
    double balance;
public:
    Account(std::string name = def_name, double balance = def_balance);
    virtual bool deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;
	virtual void print(std::ostream &os) const override;
	//a need arose for a virtual destructor
	virtual ~Account() = default;
//	std::string get_name();
};

//first making the account class an abstract class by adding pure virtual functions, remember to add virtual destructor

//we also need to override the withdraw and print function in every class for it not to be abstract

#endif