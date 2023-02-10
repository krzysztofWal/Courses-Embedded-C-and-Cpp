// Section 20
// Challenge 3  
// Maps and Sets

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <iomanip>

// Used for Part1
// Display the word and count from the 
// std::map<std::string, int>

//void display_words(const std::map<std::string, int> &words) {
//    std::cout << std::setw(12) << std::left << "\nWord"
//                << std::setw(7) << std::right << "Count"<< std::endl;
//    std::cout << "===================" << std::endl;
//    for (auto pair: words)
//        std::cout << std::setw(12) << std::left << pair.first 
//                       << std::setw(7) << std::right << pair.second << std::endl;
//}
void display_words(const std::map<std::string, int> &words) {
	
	std::cout << std::setw(15) << std::left << "Word"
				<< std::setw(7) << std::left << "Count" << std::endl
				<< std::setw(22) << std::setfill('=') << "" << std::endl << std::setfill(' ');
	for (const auto &element : words) {
		std::cout << std::setw(15) <<std::left << element.first << " " << std::setw(4) << std::right << element.second << std::endl;
	}
}

// Used for Part2
// Display the word and occurences from the 
// std::map<std::string, std::set<int>>

void display_words(const std::map<std::string, std::set<int>> &words) {
	
	std::cout << std::setw(15) << std::left << "Word"
				<< std::setw(7) << std::left << "Occurences" << std::endl
				<< std::setw(50) << std::setfill('=') << "" << std::endl << std::setfill(' ');
	for (const auto &pair : words) {
		std::cout << std::setw(15) <<std::left << pair.first
					<< "[ ";
		for (const auto &element : pair.second)
			std::cout << element << " ";
		std::cout << "]" << std::endl;
	}
}

//void display_words(const std::map<std::string, std::set<int>> &words){
//     std::cout << std::setw(12) << std::left << "\nWord"
//                << "Occurrences"<< std::endl;
//    std::cout << "=====================================================================" << std::endl;
//    for (auto pair: words) {
//        std::cout << std::setw(12) << std::left << pair.first 
//                       << std::left << "[ ";
//        for (auto i: pair.second) 
//            std::cout << i << " ";
//        std::cout << "]" << std::endl;
//    }
//}

// This function removes periods, commas, semicolons and colon in 
// a string and returns the clean version
std::string clean_string(const std::string &s) {
    std::string result;
    for (char c: s) {
        if (c == '.' || c == ',' || c == ';' || c == ':')
            continue;
        else
            result += c;
    }
    return result;
}

// Part1 process the file and builds a map of words and the 
// number of times they occur in the file

void part1() {
    std::map<std::string, int> words;
    std::string line;       
    std::string word;   
    std::ifstream in_file {"../words.txt"};
    if (in_file) {
        
		while (in_file >> word) {
//			auto indicator = words.insert(std::make_pair(clean_string(word), 1));
//			if (indicator.second == false){
//				words[clean_string(word)] +=1;
//			}
			words[clean_string(word)]++;
			//if we dont have that key it is put there and probably initialized with zero
		}
        
        in_file.close();
        display_words(words);
    } else {
        std::cerr << "Error opening input file" << std::endl;
    }
}
    
// Part2 process the file and builds a map of words and a 
// set of line numbers in which the word appears
void part2() {
    std::map<std::string, std::set<int>> words;
    std::string line;
    std::string word;
    std::ifstream in_file {"../words.txt"};
	int counter {1};
    if (in_file) {
		
		while (std::getline(in_file, line)) {
//			std:: cout << line;
			std::stringstream ss {line};
			while (ss >> word) {
//				std::cout << word;
//				auto indicator = words.insert(std::pair<std::string, std::set<int>> {clean_string(word),{counter}});
//				if (indicator.second == false) {
//					indicator.first->second.insert(counter);
//				}
				words[clean_string(word)].insert(counter);
			}
			counter++;
		}
        // You implement this code
        
        in_file.close();
        display_words(words);
    } else {
        std::cerr << "Error opening input file" << std::endl;
    }
}

int main() {
    part1();
    part2();

//	std::map<std::string, int> mapa;	
//	std::cout << mapa["Kluseczka"];
//	display_words(mapa);

    return 0;
}

