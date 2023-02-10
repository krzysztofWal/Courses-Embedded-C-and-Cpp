// Section 19
// Challenge 4
// Copy Romeo and Juliet with line numbers
#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
	std::ifstream in_file;
	std::ofstream out_file;
	std::string line;
	int lineNumber{0};
	
	in_file.open("../romeoandjuliet");
	out_file.open("../output.txt");
	
	if (!in_file) {
		std::cerr << "There was a problem opening the file";
		return 1;
	}
	
	if (!out_file) {
		std::cerr << "There was a problem opening the output file";
		return 1;
	}
	

	while (std::getline(in_file,line)) {
		
		if (!line.empty()) {
			out_file << std::setw(15) << std::left << lineNumber;
			lineNumber++;
		}
		out_file << line << std::endl;
	}

	
	in_file.close();
	out_file.close();
    return 0;
}
