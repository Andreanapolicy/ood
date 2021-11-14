#pragma once
#include <stdexcept>

class CWrongShapeException : public std::invalid_argument
{
public:
	CWrongShapeException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};