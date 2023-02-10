// Section 20
// Challenge 1
// Identifying palindrome strings using a deque
#include <cctype>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

template <typename T>
void display(const T &container){
	for (const auto &element : container)
		std::cout << element;
	std::cout << std::endl;
}

bool is_palindrome(const std::string& s)
{
    // You must implement this function.
    // Since we are learning the STL - use a deque to solve the problem.
    std::deque<char> temp1;
//	std::deque<char> temp2;
	char c1{};
	char c2{};

	for (const char &x : s){
		if (isalpha(x)) {
//		x=toupper(x);
		temp1.push_back(toupper(x));
//		temp2.push_front(x);
		}
	}
	
//	display(temp1);
//	
	while(temp1.size() > 1) {
		c1 = temp1.front();
		c2 = temp1.back();
		temp1.pop_front();
		temp1.pop_back();
		if (c1 != c2)
			return false;
	}
	
	return true;
}
	


//	display(temp1);
//	display(temp2);

	

//	if (temp1 == temp2)
//		return true;
	
//	return false;
//}

int main()
{

//	std::cout << is_palindrome("IDI");
    std::vector<std::string> test_strings{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };
   
    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    for(const auto& s : test_strings) {
        std::cout << std::setw(8) << std::left << is_palindrome(s)  << s << std::endl;
    }
	
    std::cout << std::endl;
    return 0;
}