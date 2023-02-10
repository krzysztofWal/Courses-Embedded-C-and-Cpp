// Section 15
// Challenge 
#include <iostream>
#include <vector>
#include "Savings_Account.h"
#include "Account_Util.h"
#include "Trust_Account.h"

using namespace std;

int main() {
    cout.precision(2);
    cout << fixed;
   
    // Accounts
    vector<Account> accounts;
    accounts.push_back(Account {});
    accounts.push_back(Account {"Larry"});
    accounts.push_back(Account {"Moe", 2000} );
    accounts.push_back(Account {"Curly", 5000} );
    
    display(accounts);
    deposit(accounts, 1000);
    withdraw(accounts,2000);
    
    // Savings 

    vector<Savings_Account> sav_accounts;
    sav_accounts.push_back(Savings_Account {} );
    sav_accounts.push_back(Savings_Account {"Superman"} );
    sav_accounts.push_back(Savings_Account {"Batman", 2000} );
    sav_accounts.push_back(Savings_Account {"Wonderwoman", 5000, 5.0} );

    display(sav_accounts);
    deposit(sav_accounts, 1000);
    withdraw(sav_accounts, 2000);
    
	//Checking
	 vector<Checking_Account> check_accounts;
	 
    check_accounts.push_back(Checking_Account {} );
    check_accounts.push_back(Checking_Account {"Kirk"} );
    check_accounts.push_back(Checking_Account {"Spock", 2000} );
    check_accounts.push_back(Checking_Account {"Bones", 5000} );

    display(check_accounts);
    deposit(check_accounts, 1000);
    withdraw(check_accounts, 2000);
	
	//Trust
	 vector<Trust_Account> trust_accounts;
	 
    trust_accounts.push_back(Trust_Account {} );
    trust_accounts.push_back(Trust_Account {"Matt", 10000} );
    trust_accounts.push_back(Trust_Account {"David", 20000, 1} );
    trust_accounts.push_back(Trust_Account {"Peter", 30000, 2.5} );

    display(trust_accounts);
	deposit(trust_accounts, 1000);
    withdraw(trust_accounts, 3000);
	cout << endl << trust_accounts[2].get_count() << endl;
    withdraw(trust_accounts, 1000);
	cout << endl << trust_accounts[2].get_count() << endl;
    withdraw(trust_accounts, 1000);
	cout << endl << trust_accounts[2].get_count() << endl;
	withdraw(trust_accounts, 1000);
	cout << endl << trust_accounts[2].get_count() << endl;
    return 0;
}

