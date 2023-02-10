// Section 8 Challenge
/*
	For this program I will be using US dollars and cents.
	
    Write a program that asks the user to enter the following:
	An integer representing the number of cents 
    	
	You may assume that the number of cents entered is greater than or equal to zero
    
	The program should then display how to provide that change to the user.
	
	In the US:
		1 dollar is 100 cents
		1 quarter is 25 cents
		1 dime is 10 cents
		1 nickel is 5 cents, and
		1 penny is 1 cent.
		
	Here is a sample run:
	
	Enter an amount in cents :  92
	
	You can provide this change as follows:
	dollars    : 0
	quarters : 3
	dimes     : 1
	nickels   : 1
	pennies  : 2
	
	Feel free to use your own currency system.
	Also, think of how you might solve the problem using the modulo operator.

	Have fun and test your program!!

*/
#include <iostream>

using namespace std;

int main() {

	cout << "Elo elo, would you be so kind to enter the number of cents? ";

	int cents {0};
	cin >> cents;
	
	cout << "Thank you" << endl;
	
	int numberOfDollars{0}, numberOfQuarters{0}, numberOfDimes{0}, numberOfNickles{0}, numberOfPennies{0};
	
	const int dollarValue{100};
	const int quarterValue{25};
	const int dimeValue{10};
	const int nickelValue{5};
	
	
	numberOfDollars = cents / dollarValue;
//	cents -= numberOfDollars * dollarValue;
	cents %= dollarValue;
	cout << "Dollars: \t" << numberOfDollars <<  endl;
	
	numberOfQuarters = cents / quarterValue;
//	cents -= numberOfQuarters * quarterValue;
	cents %= quarterValue;
	cout << "Quarters: \t" << numberOfQuarters << endl;
	
	numberOfDimes = cents / dimeValue;
//	cents -= numberOfDimes * dimeValue;
	cents %= dimeValue;
	cout << "Dimes:" << "\t\t" << numberOfDimes << endl;
	
	numberOfNickles = cents / nickelValue;
//	cents -= numberOfNickles * nickelValue;
	cents %= nickelValue;
	cout << "Nickles: \t" << numberOfNickles << endl;
	
	numberOfPennies = cents;
	cout << "Pennies: \t" << numberOfPennies << endl;

    cout << endl;
    return 0;
}

