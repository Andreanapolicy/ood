#pragma once
#include "../Series/Series.h"
#include "OutputStream.h"
#include <random>

class COutputStreamDecorator : public IOutputStream
{
protected:
	COutputStreamDecorator(IOutputStreamPtr&& outputStream)
		: m_stream(std::move(outputStream))
	{
	}

	IOutputStreamPtr m_stream;
};

class CCompressedOutputStream : public COutputStreamDecorator
{
public:
	CCompressedOutputStream(IOutputStreamPtr&& outputStream)
		: COutputStreamDecorator(std::move(outputStream))
	{
	}

	~CCompressedOutputStream()
	{
		WriteSeries();
	}

	void WriteByte(uint8_t data) override
	{
		if (m_series.size == 0)
		{
			m_series = {1, data};

			return;
		}

		if (m_series.byte == data && m_series.size < std::numeric_limits<uint8_t>::max())
		{
			m_series.size++;

			return;
		}

		WriteSeries();
		m_series = {1, data};

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

	void WriteSeries()
	{
		m_stream->WriteByte(m_series.size);
		m_stream->WriteByte(m_series.byte);
		m_series = {0, 0};
	}

	Series m_series = {0, 0};
};

class CEncryptedOutputStream: public COutputStreamDecorator
{
public:
	CEncryptedOutputStream(IOutputStreamPtr&& stream, int key)
		: COutputStreamDecorator(std::move(stream))
		, m_encryptedTable(256)
	{
		FillEncryptedTable(key);
	}

	void WriteByte(uint8_t data) override
	{
		m_stream->WriteByte(EncryptedByte(data));
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto buffer = static_cast<const uint8_t*>(srcData);

		for (auto index = 0; index < size; index++)
		{
			WriteByte(*buffer);
			++buffer;
		}
	}

private:
	void FillEncryptedTable(int key)
	{
		std::iota(m_encryptedTable.begin(), m_encryptedTable.end(), 0);
		std::shuffle(m_encryptedTable.begin(), m_encryptedTable.end(), std::mt19937(key));
	}

	uint8_t EncryptedByte(const uint8_t byte) const
	{
		return m_encryptedTable[byte];
	}

	std::vector<uint8_t> m_encryptedTable;
};