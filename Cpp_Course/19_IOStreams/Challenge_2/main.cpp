// Section 19
// Challenge 2
// Automated Grader
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

void printHeader() {
	cout << setw(25) << left << "Student" <<  "Score" << endl;
	cout << setw(30) << setfill('-') << "" << setfill(' ') << endl;
}

void printFooter(double averageScore) {
	cout << setw(30) << setfill('-') << "" << setfill(' ') << endl 
		<< setw(25) << left << setprecision(1) << fixed << "Average score" << averageScore << endl;
}

void printStudent(const string &name, int score) {
	cout << setw(25) << left << name << setw(5) << score << endl;
}

int processAnswer(const string &answer, const string &correctAnswer) {
	int score {0};
	for (size_t i{0}; i < answer.length(); i++) {	
		if (answer.at(i) == correctAnswer.at(i))
			score++;
	}
	return score;
}

int main() {
	
	
	int score{0};
	int numberOfStudents{0};
	int sumOfPoints{0};
	string correctAnswers;
	string answers;
	string name;
	
	fstream fp{"../responses.txt" ,ios::in};
	
	if (!fp) {
		cout << "File could not be opened";
		return 1;
	}

	fp >> correctAnswers;
	printHeader();


	while (fp >> name >> answers) {
		score = processAnswer(answers,correctAnswers);
		numberOfStudents++;
		sumOfPoints += score;
		printStudent(name, score);
	}
	
	printFooter(static_cast<double>(sumOfPoints)/numberOfStudents);
	
	fp.close();
    return 0;
}

