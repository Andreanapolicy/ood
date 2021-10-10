#pragma once
#include <stdexcept>

class InvalidNameOfShapeException : std::runtime_error
{
public:
	InvalidNameOfShapeException(const std::string& message)
		: std::runtime_error(message)
	{
	}

	std::string GetMessage() const
	{
		return this->what();
	}
};