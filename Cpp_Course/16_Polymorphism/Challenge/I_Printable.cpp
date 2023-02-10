#include "I_Printable.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const I_Printable &obj) {
	obj.print(os);
	os << std::endl;
	return os;
}

//print is a pure virtual function so we do not need to implement it; cause I don't think it would make sense
//but who knows

//operator << odwołuje się do printa który just pvf i jest override dla niego w każdej klasie