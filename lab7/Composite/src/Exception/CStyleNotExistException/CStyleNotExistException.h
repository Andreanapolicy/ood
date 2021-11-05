#pragma once
#include <stdexcept>

class CStyleNotExistException : public std::invalid_argument
{
public:
	CStyleNotExistException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};