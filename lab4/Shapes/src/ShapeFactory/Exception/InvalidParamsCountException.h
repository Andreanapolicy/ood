#pragma once
#include <stdexcept>

class InvalidParamsCountException : public std::runtime_error
{
public:
	InvalidParamsCountException(const std::string& message)
	 	: std::runtime_error(message)
	{
	}

	std::string GetMessage() const
	{
		return this->what();
	}
};