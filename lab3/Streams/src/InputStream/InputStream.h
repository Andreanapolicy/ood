#pragma once
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>

class IInputStream
{
public:
	virtual bool IsEOF() const = 0;

	virtual uint8_t ReadByte() = 0;

	virtual std::streamsize ReadBlock(void* dstData, std::streamsize dataSize) = 0;

	virtual ~IInputStream() = default;
};

typedef std::unique_ptr<IInputStream> IInputStreamPtr;

class CFileInputStream : public IInputStream
{
public:
	CFileInputStream(const std::string& fileName)
	{
		m_stream.open(fileName);

		if (!m_stream.is_open())
		{
			throw std::ios_base::failure("Error. Can not open \'" + fileName + "\' file");
		}
	}

	bool IsEOF() const override
	{
		return m_stream.eof();
	}

	uint8_t ReadByte() override
	{
		char byte;
		m_stream.get(byte);

		if (IsEOF())
		{
			throw std::ios_base::failure("Error. Can not read");
		}

		return static_cast<uint8_t>(byte);
	}

	std::streamsize ReadBlock(void* dstData, std::streamsize dataSize) override
	{
		m_stream.read(static_cast<char*>(dstData), dataSize);

		if (m_stream.bad())
		{
			throw std::ios_base::failure("Error. Can not read block");
		}

		return m_stream.gcount();
	}

private:
	std::ifstream m_stream;
};

class CMemoryInputStream : public IInputStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& memory)
		: m_stream(memory)
	{
	}

	bool IsEOF() const override
	{
		return m_pos == m_stream.size();
	}

	uint8_t ReadByte() override
	{
		if (IsEOF())
		{
			throw std::ios_base::failure("Error. Can not read");
		}

		auto value = m_stream[m_pos];
		++m_pos;

		return value;
	}

	std::streamsize ReadBlock(void* dstData, std::streamsize dataSize) override
	{
		if (dataSize > m_stream.size() - m_pos )
		{
			dataSize = m_stream.size() - m_pos;
		}

		auto buffer = static_cast<uint8_t*>(dstData);
		for (std::streamsize index = 0; index < dataSize; index++)
		{
			*buffer = m_stream[m_pos];
			++m_pos;
			++buffer;
		}

		return dataSize;
	}

private:
	std::vector<uint8_t>& m_stream;

	size_t m_pos = 0;
};