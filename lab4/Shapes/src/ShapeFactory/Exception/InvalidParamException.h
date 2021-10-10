#pragma once
#include <stdexcept>

class InvalidParamException : std::runtime_error
{
public:
	InvalidParamException(const std::string& message)
		: std::runtime_error(message)
	{
	}

	std::string GetMessage() const
	{
		return this->what();
	}
};