#pragma once
#include <stdexcept>

class ShapesIndexOutOfRange : public std::runtime_error
{
public:
	ShapesIndexOutOfRange(const std::string& message)
		: std::runtime_error(message)
	{
	}
};