#pragma once
#include <stdexcept>

class CWrongItemException : public std::invalid_argument
{
public:
	CWrongItemException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};