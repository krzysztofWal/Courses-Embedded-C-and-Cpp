// Section 19
// Challenge 3
// Word counter
#include <iostream>
#include <string>
#include <fstream>

bool isTheWordThere(std::string search, std::string source) {
	if (source.find(search, 0) == std::string::npos)
		return false;
	else
		return true;
}

std::string toUpper(std::string lowerCase, bool flag) {
	std::string temp;
	char tempChar;
	for (size_t i{0}; i < lowerCase.size(); i++) {
		tempChar = lowerCase.at(i);
		if (flag)
			temp += toupper(tempChar);
		else
			temp += tempChar;
	}
	return temp;
}

int main() {
    /*
	std::string example {"Rozrewolweryzowany rewolwerowiec z rozrewolweryzowanym rewolwerem rozrewolweryzował rewolwer rozrewolweryzowanego rewolwerowca"};
	size_t position;
	
	position = example.find("mienso", 0);
	
	std::cout << position << std::endl << example.npos;
    */
	std::fstream text;
	std::string word;
	std::string search;
	int repeatNumber{0};
	int wordNumber{0};
	
	text.open("../romeoandjuliet.txt");
	
	if(!text) {
		std::cerr << "File could not be opened" << std::endl;
	}

	std::cout << "What word do you desire? ";
	std::cin >> search;
	
	while (text >> word) {
		if (isTheWordThere(toUpper(search,true), toUpper(word,true))) {
			repeatNumber++;
//			std::cout << word << " ";
		}
		wordNumber++;
	}
	
    std::cout << wordNumber << " words were searched " << std::endl
			 << "The word you were looking for was found " << repeatNumber << " times" << std::endl;
	
	text.close();
	return 0;
}

