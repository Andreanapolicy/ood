#pragma once
#include <stdexcept>

class CInvalidParamsException : public std::invalid_argument
{
public:
	CInvalidParamsException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};
