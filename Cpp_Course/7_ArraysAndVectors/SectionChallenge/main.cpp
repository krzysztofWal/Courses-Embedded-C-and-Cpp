#include <iostream>
#include <vector>

using namespace std;

int main(){
	//defining empty vectors
	vector <int> vector1;
	vector <int> vector2;
	
	// adding values dynamically to the vector
	vector1.push_back(10);
	vector1.push_back(20);
	
	cout << "The elements in the first vector: " << endl;
	cout << vector1.at(0) << endl;
	cout << vector1.at(1) << endl;
	cout << "This vector has " << vector1.size() << " elements" << endl;
	
	vector2.push_back(100);
	vector2.push_back(200);
	
	cout << "\nThe elements in the second vector: " << endl;
	cout << vector2.at(0) << endl;
	cout << vector2.at(1) << endl;
	cout << "This vector has " << vector2.size() << " elements" << endl;
	
	vector <vector<int>> vector_2d;
	
	vector_2d.push_back(vector1);
	vector_2d.push_back(vector2);
	
	cout << "\n2D vector" << endl;
	cout << vector_2d.at(0).at(0) << " " << vector_2d.at(0).at(1) << endl;
	cout << vector_2d.at(1).at(0) << " " << vector_2d.at(1).at(1) << endl;
	//cout << "This vector has " << vector_2d.size() << " elements" << endl;
	
	vector1.at(0) = 1000;
	
	cout << "\n2D vector after change" << endl;
	cout << vector_2d.at(0).at(0) << " " << vector_2d.at(0).at(1) << endl;
	cout << vector_2d.at(1).at(0) << " " << vector_2d.at(1).at(1) << endl;
	
	cout << "\nThe elements in the first vector after change: " << endl;
	cout << vector1.at(0) << endl;
	cout << vector1.at(1) << endl;
	
	return 0;
}
