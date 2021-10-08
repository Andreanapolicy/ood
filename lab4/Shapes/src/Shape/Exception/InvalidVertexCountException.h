#pragma once
#include "stdexcept"

class InvalidVertexCountException : public std::runtime_error
{
public:
	InvalidVertexCountException(const std::string& message)
		: std::runtime_error(message)
	{
	}
};