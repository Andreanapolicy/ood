#pragma once
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>

class IOutputStream
{
public:
	virtual void WriteByte(uint8_t data) = 0;

	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputStream() = default;
};

typedef std::unique_ptr<IOutputStream> IOutputStreamPtr;

class CFileOutputStream : public IOutputStream
{
public:
	CFileOutputStream(const std::string& fileName)
		: m_stream(fileName, std::ios::binary)
	{
		if (!m_stream.is_open())
		{
			throw std::ios_base::failure("Error. Can not open \'" + fileName + "\' file");
		}
	}

	void WriteByte(uint8_t data) override
	{
		WriteBlock(&data, 1);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		m_stream.write(static_cast<const char*>(srcData), size);
		if (m_stream.fail() || m_stream.bad())
		{
			throw std::ios_base::failure("Error. Can not write to file");
		}

		m_stream.flush();
	}

private:
	std::ofstream m_stream;
};

class CMemoryOutputStream : public IOutputStream
{
public:
	CMemoryOutputStream(std::vector<uint8_t>& memory)
		: m_stream(memory)
	{
	}

	void WriteByte(uint8_t data) override
	{
		try
		{
			m_stream.push_back(data);
		}
		catch (const std::exception& exception)
		{
			throw std::ios_base::failure("Error. Can not write to memory");
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto buffer = static_cast<const uint8_t*>(srcData);

		for (std::streamsize index = 0; index < size; index++)
		{
			WriteByte(*buffer);
			buffer++;
		}
	}

private:
	std::vector<uint8_t>& m_stream;
};