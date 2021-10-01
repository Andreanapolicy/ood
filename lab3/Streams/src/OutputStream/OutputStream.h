#pragma once
#include <iomanip>
#include <string>
#include <cstdint>

class IOutputStream
{
public:
	virtual void WriteBlock(uint8_t data) = 0;

	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputStream() = 0;
};

