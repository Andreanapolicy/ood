#pragma once
#include <stdexcept>

class CEmptyShapeException : public std::invalid_argument
{
public:
	CEmptyShapeException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};