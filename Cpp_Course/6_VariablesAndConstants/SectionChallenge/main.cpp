#include <iostream>

using namespace std;

int main(){
	cout << "Elo elo, czy dwa zero (jest juz PUZYNO)" << endl;
	
	cout << "\nHow many  small rooms would you like to have cleaned? ";
	int numberOfSmallRooms {0};
	cin >> numberOfSmallRooms;
	
	cout << "How many large rooms would you like to have cleaned? ";
	int numberOfLargeRooms {0};
	cin >> numberOfLargeRooms;
	
	//declaring constants used in calculations
	const double pricePerSmallRoom {25.0};
	const double pricePerLargeRoom {35.0};
	const double salesRate {0.06};
	const int estExpiry {30}; //days
	
	cout << "\nEstimate for carpet cleaning service" << endl;
	
	cout << "Number of small rooms: " << numberOfSmallRooms << endl;
	cout << "Number of large rooms: " << numberOfLargeRooms << endl;
	
	cout << "Price per small room: $ " << pricePerSmallRoom <<endl;
	cout << "Price per large room: $ " << pricePerLargeRoom <<endl;
	
	double cost {pricePerSmallRoom*numberOfSmallRooms+pricePerLargeRoom*numberOfLargeRooms};
	double tax {pricePerSmallRoom*numberOfSmallRooms*salesRate+pricePerLargeRoom*numberOfLargeRooms*salesRate};
	
	cout << "Cost: $ " << cost << endl;
	cout << "Tax: $ " << tax << endl;
	cout<< "===============================" << endl;
	cout << "Total estimate: $" << cost + tax << endl;
	cout << "Ten estymat waznosc trzyma przez dni nastepnych " << estExpiry << endl;

return 0;
}