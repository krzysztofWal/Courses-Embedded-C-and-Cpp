// Section 9
// Challenge
/*    
    This challenge is about using a collection (list) of integers and allowing the user
    to select options from a menu to perform operations on the list.
    
    Your program should display a menu options to the user as follows:
    
    P - Print numbers
    A - Add a number
    M - Display mean of the numbers
    S - Display the smallest number
    L - Display the largest number
    Q - Quit

    Enter your choice:
    
The program should only accept valid choices from the user, both upper and lowercase selections should be allowed.
If an illegal choice is made, you should display, "Unknown selection, please try again" and the menu options should be
displayed again.


If the user enters 'P' or 'p', you should display all of the elements (ints) in the list.
If the list is empty you should display "[] - the list is empty"
If the list is not empty then all the list element should be displayed inside square brackets separated by a space. 
For example, [ 1 2 3 4 5 ]
      
If the user enters 'A' or 'a' then you should prompt the user for an integer to add to the list 
which you will add to the list and then display it was added. For example, if the user enters 5
You should display, "5 added".
Duplicate list entries are OK

If the user enters 'M' or 'm'  you should calculate the mean or average of the elements in the list and display it.
If the list is empty you should display, "Unable to calculate the mean - no data"

If the user enters 'S' or 's' you should display the smallest element in the list.
For example, if the list contains [2 4 5 1],  you should display, "The smallest number is 1"
If the list is empty you should display, "Unable to determine the smallest number - list is empty"

If the user enters 'L' or 'l' you should display the largest element in the list
For example, if the list contains [2 4 5 1], you should display, "The largest number is 5"
If the list is empty you should display, "Unable to determine the largest number - list is empty"

If the user enters 'Q' or 'q' then you should display 'Goodbye" and the program should terminate.

Before you begin. Write out the steps you need to take and decide in what order they should be done.
Think about what loops you should use as well as what you will use for your selection logic.

This exercise can be challenging! It may likely take a few attempts before you complete it -- that's OK!

Finally, be sure to test your program as you go and at the end.

Hint: Use a vector!

Additional functionality if you wish to extend this program.

- search for a number in the list and if found display the number of times it occurs in the list
- clearing out the list (make it empty again) (Hint: the vector class has a .clear() method)
- don't allow duplicate entries
- come up with your own ideas!

Good luck!

*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    /*
	  
	 */
	char TypeIn{};
	vector<int> vec {2, 7, 8, 9, 1};
	//menu
	cout << "Hello there" << endl << endl << "P - Print numbers" << endl 
		<< "A - Add a number" << endl 
		<< "M - Display mean of the numbers" << endl
		<< "S - Display the smallest number" << endl
		<< "L - Display the largest amount" << endl
		<< "C - Clear the data" << endl
		<< "Q - Quit";
    
	do {
	cout << endl << endl << "Enter your choice: ";
	cin >> TypeIn;
	cout << endl;
		switch (TypeIn) {
			case 'P':
			case 'p': 
				if (vec.size() != 0){
					cout << "[ ";
					for (auto var : vec)
						cout << var << " ";
				cout << "]";
				} else cout << "[] - The list is empty";
				break;
			case 'A':
			case 'a':
				{
				cout << "Type in the number you want to add to the list: ";
				int number{};
				cin >> number;
				vec.push_back(number);
				cout << number << " added" ;
				}
				break;
			case 'M':
			case 'm':
				{
				double sum{};
				if (vec.size() != 0){
					for (auto var : vec)
						sum += var;
					cout << "Mean is " << (sum / vec.size());
				} else cout << "Unable to calculate mean - no data";
				}
				break;
			case 'S':
			case 's':
				{
				int min{vec.at(0)};
				if (vec.size() != 0){
					for (auto var : vec)
						if(var < min) min = var;
					cout << "The smallest number is " << min;
				} else cout << "Unable to determine the smallest number - list is empty";
				break;
				}
			case 'L':
			case 'l':
				{
				int max{};
				if (vec.size() != 0){
					for (auto var : vec)
						if(var > max) max = var;
					cout << "The largest number is " << max;
				} else cout << "Unable to determine the largest number - list is empty";
				}
				break;
			case 'C':
			//clearing the data
			case 'c':
				char TypeCheck;
				cout << "Are you sure you want to clear the data? (Y/N) ";
				cin >> TypeCheck;
				if (TypeCheck == 'y' || TypeCheck == 'Y'){
					vec.clear();
					cout << "Data was cleared";
				} else if (TypeCheck == 'N' || TypeCheck == 'n') {
					cout << "Ok, data wasn't cleared";
				} else cout << "You didn't type Y or N, if you do want to clear the data you should try again";
				break;
			case 'q':
			case 'Q':
				cout << "Goodbye!";
				break;
			default:
				cout << "I am not sure what ypu want to achieve, perhaps you should choose again";
		}
	
		
	} while (TypeIn != 'q' && TypeIn != 'Q');
		
	cout << endl << endl;
    return 0;
}

