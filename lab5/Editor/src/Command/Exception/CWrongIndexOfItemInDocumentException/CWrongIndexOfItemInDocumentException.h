#pragma once
#include <stdexcept>

class CWrongIndexOfItemInDocumentException : public std::invalid_argument
{
public:
	CWrongIndexOfItemInDocumentException(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};