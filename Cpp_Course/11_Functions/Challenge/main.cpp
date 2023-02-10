// Section 11
// Challenge 
/*
     Recall the challenge from Section 9 below.
    Your challenge for section 11 is to modularize your solution to the Section 9
    challenge by refactoring your solution so that it uses uses functions.
    
    You decide how to modularize the program.
    you can use my solution which is included in this file, or modularize your solution.
    
    Here are a few hints:
        - Create functions for each major function
        - Keep the functions small
        - Remember the Boss/Worker analogy
        - Keep the vector declaration in the main function and pass the vector object
          to any function that requires it

        DO NOT move the vector object outside main and make it a global variable.
    
        - You can start by defining a function that displays the menu
        - You can then define a function that reads the selection from the user and returns it in uppercase
        - Create functions for each menu option
        - Create functions that display the list of numbers, calculates the mean and so forth
        
    Take it one function at a time and take your time.
    If you get frustrated, take a break -- this isn't as easy as it looks the first time you do it!
    
    Finally,  don't forget to use function prototypes!
    
    Good luck -- I know you can do it!
*/
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
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

// handle functions
void handlePrint(const vector<int> &v);
void handleAdd(vector<int> &v);
void handleMean(const vector<int> &v);
void handleSmallest(const vector<int> &v);
void handleLargest(const vector<int> &v);
void handleClear(vector<int> &v);
void handleQuit(const std::vector<int> &v);
void handleNo();
void handleYes(vector<int> &v);
void handleElse();
//functions
int smallestNumber(const vector<int> &v);
int largestNumber(const vector<int> &v);
double calculateMean(const vector<int> &v);
void displayMenu();
char getSelection();
void print(const vector<int> &v);

int main() {

std::vector<int> numbers {};
char selection;

do {
	displayMenu();
	cout << "\nEnter your selection: ";
	selection = getSelection();
	switch (selection) {
		case 'P':
			handlePrint(numbers);
			break;
		case 'A':
			handleAdd(numbers);
			break;
		case 'M':
			handleMean(numbers);
			break;
		case 'S':
			handleSmallest(numbers);
			break;
		case 'L':
			handleLargest(numbers);
			break;
		case 'C':
			handleClear(numbers);
			break;
		case 'Q':
			handleQuit(numbers);
			break;
		default:
			handleElse();
		}
	} while (selection != 'Q');

    cout  << endl;
    return 0;
}

//handling functions
void handlePrint(const std::vector<int> &v){ //dun
	if (v.size() == 0)
		std::cout << "[] - the list is empty" << std::endl;
	else
		print(v);
	return;
}

void handleAdd(std::vector<int> &v){ //dun
	int number{};
	cout <<"Enter the number you want to add: ";
	cin >> number;
	v.push_back(number);
	cout << number << " added to the list" << endl;
	return;
}

void handleMean(const std::vector<int> &v){
	if (v.size() == 0)
		std::cout << "Cannot calculate mean - the list is empty" << std::endl;
	else
		cout << "The calculated mean is: " << calculateMean(v) << endl;
	return;
}

void handleSmallest(const std::vector<int> &v){
	if (v.size() == 0)
		std::cout << "Cannot find the smallest number - the list is empty" << std::endl;
	else
		cout << "The smallest number is: " << smallestNumber(v) << endl;
	return;
}

void handleLargest(const std::vector<int> &v){
	if (v.size() == 0)
		std::cout << "Cannot find the largest number - the list is empty" << std::endl;
	else
		cout << "The largest number is: " << largestNumber(v) << endl;
	return;
}

void handleClear(std::vector<int> &v){ //dun
	char selection;
	bool flag{};
	do {
			cout << "Are you sure you want to clear the data? (Y/N) ";
			selection=getSelection();
			switch (selection) {
			case 'Y':
				handleYes(v);
				flag = true;
				break;
			case 'N':
				handleNo();
				flag = true;
				break;
			default:
				handleElse();
				flag = false;
				break;
	}
	} while (flag == false);
	return;
}

void handleQuit(const std::vector<int> &v){
	cout << "Program terminated, go home xd" << endl;
	return;
}

void handleNo(){ //dun
	cout << "Ok, data wasn't cleared" << endl;
	return;
}

void handleYes(std::vector<int> &v){ //dun
	v.clear();
	cout << "Data cleared" << endl;
	return;
}

void handleElse(){ //dun
	cout << "I am not sure what you wanted to achieve, try once again" << endl;
	return;
}


//functions
void displayMenu(){
	cout << "\nP - Print numbers" << endl;
	cout << "A - Add a number" << endl;
	cout << "M - Display mean of the numbers" << endl;
	cout << "S - Display the smallest number" << endl;
	cout << "L - Display the largest number"<< endl;
//	cout << "D - Display menu once again" << endl;
	cout << "C - Clear the data" << endl;
	cout << "Q - Quit" << endl;
}

void print(const std::vector<int> &v){
	cout << "[ ";
	for (auto const &num: v)
		cout << num << " ";
	cout << "]" << endl;
	
}

char getSelection(){
	char selection;
	std::cin >> selection;
	return toupper(selection);
}

double calculateMean(const vector<int> &v){
	int sum{};
	for (auto const &num: v)
		sum += num;
	return static_cast<double>(sum)/v.size();
}

int smallestNumber(const vector<int> &v){
	int smallest{v.at(0)};
	for (auto const &num: v)
		if (num < smallest) smallest=num;
	return smallest;
}

int largestNumber(const vector<int> &v){
	int largest{v.at(0)};
	for (auto const &num: v)
		if (num > largest) largest=num;
	return largest;
}