#include <iostream>
#include <cstring>
#include "Mystring.h"

 // No-args constructor
Mystring::Mystring() 
    : str{nullptr} {
    str = new char[1];
    *str = '\0';
}

// Overloaded constructor
Mystring::Mystring(const char *s) 
    : str {nullptr} {
        if (s==nullptr) {
            str = new char[1];
            *str = '\0';
        } else {
            str = new char[strlen(s)+1];
            strcpy(str, s);
        }
}

// Copy constructor
Mystring::Mystring(const Mystring &source) 
    : str{nullptr} {
        str = new char[strlen(source.str)+ 1];
        strcpy(str, source.str);
 //       std::cout << "Copy constructor used" << std::endl;

}

// Move constructor
Mystring::Mystring( Mystring &&source) 
    :str(source.str) {
        source.str = nullptr;
//        std::cout << "Move constructor used" << std::endl;
}

 // Destructor
Mystring::~Mystring() {
    delete [] str;
}

 // Copy assignment
Mystring &Mystring::operator=(const Mystring &rhs) {
//    std::cout << "Using copy assignment" << std::endl;

    if (this == &rhs) 
        return *this;
    delete [] str;
    str = new char[strlen(rhs.str) + 1];
    strcpy(str, rhs.str);
    return *this;
}

// Move assignment
Mystring &Mystring::operator=( Mystring &&rhs) {
 //   std::cout << "Using move assignment" << std::endl;
    if (this == &rhs) 
        return *this;
    delete [] str;
    str = rhs.str;
    rhs.str = nullptr;
    return *this;
}


// Display method
void Mystring::display() const {
    std::cout << str << " : " << get_length() << std::endl;
}

 // getters
 int Mystring::get_length() const { return strlen(str); }
 const char *Mystring::get_str() const { return str; }

// overloaded insertion operator
std::ostream &operator<<(std::ostream &os, const Mystring &rhs) {
    os << rhs.str;
    return os;
}

// overloaded extraction operator
std::istream &operator>>(std::istream &in, Mystring &rhs) {
    char *buff = new char[1000];
    in >> buff;
    rhs = Mystring{buff};
    delete [] buff;
    return in;
}

//overloaded equality operators
bool Mystring::operator==(const Mystring &rhs) const {
	return (std::strcmp(this->str,rhs.str) == 0);
}
	
bool Mystring::operator!=(const Mystring &rhs) const {
	return (std::strcmp(this->str,rhs.str) != 0);
}

//unary minus operator
Mystring Mystring::operator-() {
	char *buff = new char[std::strlen(this->str) + 1];
	std::strcpy(buff,str);
	for (size_t i{0}; i < std::strlen(this->str); i++) {
		buff[i] = std::tolower(str[i]);
	}
	Mystring temp {buff};
	delete [] buff;
	return temp;
}

//concatenate
Mystring Mystring::operator+(const Mystring &rhs) const {
	char *buff = new char[std::strlen(this->str) + std::strlen(rhs.str) + 1];
	strcpy(buff, this->str);
	strcat(buff, rhs.str);
	Mystring temp {buff};
	delete [] buff;
	return temp;
}

//lexically greater
bool Mystring::operator>(const Mystring &rhs) const {
	return strcmp(this->str,rhs.str) > 0; //this jest lexically greater than rhs 
}

//lexically smaller
bool Mystring::operator<(const Mystring &rhs) const {
	return strcmp(this->str,rhs.str) < 0; //this jest lexically smaller than rhs 
}

// adding the string to the left-hand-side (this)
Mystring &Mystring::operator+=(const Mystring &rhs) {
	*this = *this + rhs;
	return *this;
}
//repeating the string

Mystring Mystring::operator*(const Mystring &lhs, size_t howManyTimes) const {
	if (howManyTimes == 0) {
		Mystring temp;
		return temp;
	}
	char *buff = new char[strlen(this->str) * howManyTimes + 1];
	strcpy(buff, this->str);
	size_t i =1; 
	do {
		strcat(buff, this->str);
		i++;
	} while ( i < howManyTimes );
	Mystring temp {buff};
	delete [] buff;
	return temp;
}

Mystring &Mystring::operator*=(int howManyTimes) {
	*this = *this * howManyTimes;
	return *this;
}

//pre and post increment

Mystring &Mystring::operator++()   {  // pre-increment
   // do what ever you want increment do to - maybe make all characters uppercase?
	for (size_t i{0}; i < std::strlen(this->str); i++)
		lhs.str[i] = std::toupper(str[i]);
	return *this;
}


Mystring Mystring::operator++(int) {   // post-increment
   Mystring temp (*this);       // make a copy
   operator++();                    // call pre-increment - make sure you call pre-increment!
   return temp;                     // return the old value
}
//incrementing behind 