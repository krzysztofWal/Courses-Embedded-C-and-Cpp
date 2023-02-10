#ifndef _MYSTRING_H_
#define _MYSTRING_H_

class Mystring
{
    friend std::ostream &operator<<(std::ostream &os, const Mystring &rhs);
    friend std::istream &operator>>(std::istream &in, Mystring &rhs);

private:
    char *str;      // pointer to a char[] that holds a C-style string
public:
    Mystring();                                                         // No-args constructor
    Mystring(const char *s);                                     // Overloaded constructor
    Mystring(const Mystring &source);                    // Copy constructor
    Mystring( Mystring &&source);                         // Move constructor
    ~Mystring();
	
	void display() const;
    int get_length() const;                                      // getters
    const char *get_str() const;                                                // Destructor
    
    Mystring &operator=(const Mystring &rhs);     // Copy assignment
	Mystring &operator=(Mystring &&rhs);
	Mystring &operator+=(const Mystring &rhs);
	Mystring &operator*=(int howManyTimes);
	Mystring &operator++();
	Mystring operator-();
	Mystring operator+(const Mystring &rhs) const;
	Mystring operator*(size_t howManyTimes) const;
	
	bool operator==(const Mystring &rhs) const;
	bool operator!=(const Mystring &rhs) const;
	bool operator>(const Mystring &rhs) const;
	bool operator<(const Mystring &rhs) const;



};


#endif // _MYSTRING_H_