#ifndef _INSUFFICIENT_FUNDS_EXCEPTION_
#define _INSUFFICIENT_FUNDS_EXCEPTION_

class InsufficientFundsException: public std::exception 
{
public:
	InsufficientFundsException() = default;
	~InsufficientFundsException() = default;
	virtual const char* what() const noexcept {
		return "Insufficient funds exception";
	}
};

#endif