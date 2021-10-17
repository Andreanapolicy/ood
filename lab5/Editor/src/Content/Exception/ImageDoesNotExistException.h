#pragma once
#include <stdexcept>

class ImageDoesNotExistException : public std::invalid_argument
{
public:
	ImageDoesNotExistException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};