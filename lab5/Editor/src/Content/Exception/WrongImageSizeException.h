#pragma once
#include <stdexcept>

class WrongImageSizeException : public std::invalid_argument
{
public:
	WrongImageSizeException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};
