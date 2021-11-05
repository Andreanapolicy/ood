#pragma once
#include <stdexcept>

class CWrongShapeIndexException : public std::invalid_argument
{
public:
	CWrongShapeIndexException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};