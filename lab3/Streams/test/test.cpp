#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/InputStream/InputStream.h"
#include "../src/InputStream/InputStreamDecorator.h"
#include "../src/OutputStream/OutputStream.h"
#include "../src/OutputStream/OutputStreamDecorator.h"

std::string GetDataFromFile(std::string const& fileName)
{
	std::ifstream stream;
	stream.open(fileName);

	if (!stream.is_open())
	{
		throw std::ios_base::failure(fileName + " could not be opened");
	}

	return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}

TEST_CASE("check input file stream")
{
	const std::string TEXT_FILE = "../test/text_file.txt";
	const std::string EMPTY_FILE = "../test/empty_file.txt";
	const std::string NO_EXIST_FILE = "../test/no_exist_file.txt";

	SECTION("check constructor of file input stream")
	{
		GIVEN("creating file with no existing file name")
		{
			THEN("throw exception in construction: std::ios_base::failure")
			{
				REQUIRE_THROWS_AS(CFileInputStream(NO_EXIST_FILE), std::ios_base::failure);
			}
		}

		GIVEN("creating file with existing file name")
		{
			THEN("there are no throws")
			{
				REQUIRE_NOTHROW(CFileInputStream(TEXT_FILE));
			}
		}
	}

	SECTION("check reading symbols from file")
	{
		GIVEN("empty file")
		{
			CFileInputStream ifstream = CFileInputStream(EMPTY_FILE);

			WHEN("starting read")
			{
				REQUIRE_THROWS_AS(ifstream.ReadByte(), std::ios_base::failure);
			}
		}

		GIVEN("file with data")
		{
			CFileInputStream ifstream = CFileInputStream(TEXT_FILE);

			WHEN("starting read")
			{
				REQUIRE(ifstream.ReadByte() == '1');
				REQUIRE(ifstream.ReadByte() == 'V');
				REQUIRE(ifstream.ReadByte() == '#');
				REQUIRE(ifstream.ReadByte() == 'c');
				REQUIRE(ifstream.ReadByte() == '\n');
				REQUIRE(ifstream.ReadByte() == 's');
				REQUIRE(ifstream.ReadByte() == 'a');

				REQUIRE_THROWS_AS(ifstream.ReadByte(), std::ios_base::failure);

				THEN("is EOF")
				{
					REQUIRE(ifstream.IsEOF());
				}
			}

			WHEN("reading to buffer")
			{
				char buffer[4];
				REQUIRE(ifstream.ReadBlock(buffer, 4) == 4);

				THEN("in buffer: 1V#c")
				{
					REQUIRE(buffer[0] == '1');
					REQUIRE(buffer[1] == 'V');
					REQUIRE(buffer[2] == '#');
					REQUIRE(buffer[3] == 'c');
				}
			}

			WHEN("reading to buffer with size, greater then real size")
			{
				char buffer[7];
				REQUIRE(ifstream.ReadBlock(buffer, 10) == 7);

				THEN("in buffer: 1V#c")
				{
					REQUIRE(buffer[0] == '1');
					REQUIRE(buffer[1] == 'V');
					REQUIRE(buffer[2] == '#');
					REQUIRE(buffer[3] == 'c');
				}
			}
		}
	}
}

TEST_CASE("check input memory stream")
{
	std::vector<uint8_t> TEXT_MEMORY = {'a', 's', '1', '\n'};
	std::vector<uint8_t> EMPTY_MEMORY = {};

	SECTION("check reading symbols from memory")
	{
		GIVEN("empty memory")
		{
			CMemoryInputStream istream = CMemoryInputStream(EMPTY_MEMORY);

			WHEN("starting read")
			{
				REQUIRE_THROWS_AS(istream.ReadByte(), std::ios_base::failure);
			}
		}

		GIVEN("file with data")
		{
			CMemoryInputStream istream = CMemoryInputStream(TEXT_MEMORY);

			WHEN("starting read")
			{
				REQUIRE(istream.ReadByte() == 'a');
				REQUIRE(istream.ReadByte() == 's');
				REQUIRE(istream.ReadByte() == '1');
				REQUIRE(istream.ReadByte() == '\n');

				REQUIRE_THROWS_AS(istream.ReadByte(), std::ios_base::failure);

				THEN("is EOF")
				{
					REQUIRE(istream.IsEOF());
				}
			}

			WHEN("reading to buffer")
			{
				char buffer[4];
				REQUIRE(istream.ReadBlock(buffer, 4) == 4);

				THEN("in buffer: 1V#c")
				{
					REQUIRE(buffer[0] == 'a');
					REQUIRE(buffer[1] == 's');
					REQUIRE(buffer[2] == '1');
					REQUIRE(buffer[3] == '\n');
				}
			}
		}
	}
}

TEST_CASE("check output file stream")
{
	std::string INVALID_FILE_NAME = "text/file.txt";
	std::string VALID_FILE_NAME = "text_file.txt";

	SECTION("check writing symbols to file")
	{
		GIVEN("not valid name of file")
		{
			THEN("exception, can not open file")
			{
				REQUIRE_THROWS_AS(CFileOutputStream(INVALID_FILE_NAME), std::ios_base::failure);
			}
		}

		GIVEN("file with correct name")
		{
			CFileOutputStream istream = CFileOutputStream(VALID_FILE_NAME);

			WHEN("starting writing")
			{
				REQUIRE_NOTHROW(istream.WriteByte('1'));
				REQUIRE_NOTHROW(istream.WriteByte('C'));
				REQUIRE_NOTHROW(istream.WriteByte('c'));
				REQUIRE_NOTHROW(istream.WriteByte('#'));

				THEN("data in file will be '1Cc#'")
				{
					REQUIRE(GetDataFromFile(VALID_FILE_NAME) == "1Cc#");
				}
			}

			WHEN("writing buffer")
			{
				char buffer[4] = {'1', 'C', '#', '\n'};

				REQUIRE_NOTHROW(istream.WriteBlock(buffer, 4));

				THEN("data in file will be '1C#/n'")
				{
					REQUIRE(GetDataFromFile(VALID_FILE_NAME) == "1C#\n");
				}
			}
		}
	}
}

TEST_CASE("check output memory stream")
{
	std::vector<uint8_t> MEMORY_OUTPUT = {};

	SECTION("check writing symbols to memory")
	{
		GIVEN("memory")
		{
			CMemoryOutputStream istream = CMemoryOutputStream(MEMORY_OUTPUT);

			WHEN("starting writing")
			{
				REQUIRE_NOTHROW(istream.WriteByte('1'));
				REQUIRE_NOTHROW(istream.WriteByte('C'));
				REQUIRE_NOTHROW(istream.WriteByte('c'));
				REQUIRE_NOTHROW(istream.WriteByte('#'));

				THEN("data in file will be '1Cc#'")
				{
					REQUIRE(MEMORY_OUTPUT[0]);
					REQUIRE(MEMORY_OUTPUT[1]);
					REQUIRE(MEMORY_OUTPUT[2]);
					REQUIRE(MEMORY_OUTPUT[3]);
				}
			}

			WHEN("writing buffer")
			{
				char buffer[4] = {'1', 'C', '#', '\n'};

				REQUIRE_NOTHROW(istream.WriteBlock(buffer, 4));

				THEN("data in file will be '1C#/n'")
				{
					REQUIRE(MEMORY_OUTPUT[0] == '1');
					REQUIRE(MEMORY_OUTPUT[1] == 'C');
					REQUIRE(MEMORY_OUTPUT[2] == '#');
					REQUIRE(MEMORY_OUTPUT[3] == '\n');
				}
			}
		}
	}
}

TEST_CASE("check compression and decompression on memory stream")
{
	SECTION("writing by one byte")
	{
		std::vector<uint8_t> memory;

		{
			auto stream = std::make_unique<CMemoryOutputStream>(memory);
			auto compressedStream = CCompressedOutputStream(std::move(stream));

			compressedStream.WriteByte('1');
			compressedStream.WriteByte('C');
			compressedStream.WriteByte('C');
			compressedStream.WriteByte('A');
			compressedStream.WriteByte('A');
			compressedStream.WriteByte('A');
			compressedStream.WriteByte('\n');
		}

		{
			auto inStream = std::make_unique<CMemoryInputStream>(memory);
			auto decompressedStream = CDecompressedInputStream(std::move(inStream));

			REQUIRE(decompressedStream.ReadByte() == '1');
			REQUIRE(decompressedStream.ReadByte() == 'C');
			REQUIRE(decompressedStream.ReadByte() == 'C');
			REQUIRE(decompressedStream.ReadByte() == 'A');
			REQUIRE(decompressedStream.ReadByte() == 'A');
			REQUIRE(decompressedStream.ReadByte() == 'A');
		}
	}

	SECTION("writing by block")
	{
		std::vector<uint8_t> memory;
		char infoBefore[7] = {'1', 'C', 'C', 'A', 'A', 'A', '\n'};

		{
			auto stream = std::make_unique<CMemoryOutputStream>(memory);
			auto compressedStream = CCompressedOutputStream(std::move(stream));

			compressedStream.WriteBlock(infoBefore, 6);
		}

		auto inStream = std::make_unique<CMemoryInputStream>(memory);
		auto decompressedStream = CDecompressedInputStream(std::move(inStream));
		char infoAfter[6];

		REQUIRE(decompressedStream.ReadBlock(infoAfter, 6) == 6);
		REQUIRE(infoAfter[0] == infoBefore[0]);
		REQUIRE(infoAfter[1] == infoBefore[1]);
		REQUIRE(infoAfter[2] == infoBefore[2]);
		REQUIRE(infoAfter[3] == infoBefore[3]);
		REQUIRE(infoAfter[4] == infoBefore[4]);
		REQUIRE(infoAfter[5] == infoBefore[5]);
	}
}

TEST_CASE("check compression and decompression on file stream")
{
	std::string FILE_NAME = "file.txt";

	SECTION("writing by one byte")
	{
		{
			auto stream = std::make_unique<CFileOutputStream>(FILE_NAME);
			auto compressedStream = CCompressedOutputStream(std::move(stream));

			compressedStream.WriteByte('1');
			compressedStream.WriteByte('C');
			compressedStream.WriteByte('C');
			compressedStream.WriteByte('A');
			compressedStream.WriteByte('A');
			compressedStream.WriteByte('A');
			compressedStream.WriteByte('\n');
			compressedStream.WriteByte('A');
		}
		{
			auto inStream = std::make_unique<CFileInputStream>(FILE_NAME);
			auto decompressedStream = CDecompressedInputStream(std::move(inStream));

			REQUIRE(decompressedStream.ReadByte() == '1');
			REQUIRE(decompressedStream.ReadByte() == 'C');
			REQUIRE(decompressedStream.ReadByte() == 'C');
			REQUIRE(decompressedStream.ReadByte() == 'A');
			REQUIRE(decompressedStream.ReadByte() == 'A');
			REQUIRE(decompressedStream.ReadByte() == 'A');
			REQUIRE(decompressedStream.ReadByte() == '\n');
			REQUIRE(decompressedStream.ReadByte() == 'A');
		}
	}

	SECTION("writing by block")
	{
		char infoBefore[7] = {'1', 'C', 'C', 'A', 'A', 'A', '\n'};

		{
			auto stream = std::make_unique<CFileOutputStream>(FILE_NAME);
			auto compressedStream = CCompressedOutputStream(std::move(stream));

			compressedStream.WriteBlock(infoBefore, 6);
		}

		auto inStream = std::make_unique<CFileInputStream>(FILE_NAME);
		auto decompressedStream = CDecompressedInputStream(std::move(inStream));
		char infoAfter[6];

		REQUIRE(decompressedStream.ReadBlock(infoAfter, 6) == 6);
		REQUIRE(infoAfter[0] == infoBefore[0]);
		REQUIRE(infoAfter[1] == infoBefore[1]);
		REQUIRE(infoAfter[2] == infoBefore[2]);
		REQUIRE(infoAfter[3] == infoBefore[3]);
		REQUIRE(infoAfter[4] == infoBefore[4]);
		REQUIRE(infoAfter[5] == infoBefore[5]);
	}
}

TEST_CASE("check crypt and decrypt on file stream")
{
	std::string FILE_NAME = "file.txt";

	SECTION("writing by one byte")
	{
		{
			auto stream = std::make_unique<CFileOutputStream>(FILE_NAME);
			auto encryptedStream = CEncryptedOutputStream(std::move(stream), 12); // remove {}

			encryptedStream.WriteByte('1');
			encryptedStream.WriteByte('C');
			encryptedStream.WriteByte('C');
			encryptedStream.WriteByte('A');
			encryptedStream.WriteByte('A');
			encryptedStream.WriteByte('A');
			encryptedStream.WriteByte('\n');
			encryptedStream.WriteByte('A');
		}
		{
			auto inStream = std::make_unique<CFileInputStream>(FILE_NAME);
			auto decryptedStream = CDecryptedInputStream(std::move(inStream), 12);

			REQUIRE(decryptedStream.ReadByte() == '1');
			REQUIRE(decryptedStream.ReadByte() == 'C');
			REQUIRE(decryptedStream.ReadByte() == 'C');
			REQUIRE(decryptedStream.ReadByte() == 'A');
			REQUIRE(decryptedStream.ReadByte() == 'A');
			REQUIRE(decryptedStream.ReadByte() == 'A');
			REQUIRE(decryptedStream.ReadByte() == '\n');
			REQUIRE(decryptedStream.ReadByte() == 'A');
		}
	}

	SECTION("writing by block")
	{
		char infoBefore[7] = {'1', 'C', 'C', 'A', 'A', 'A', '\n'};

		{
			auto stream = std::make_unique<CFileOutputStream>(FILE_NAME);
			auto compressedStream = CEncryptedOutputStream(std::move(stream), 12);

			compressedStream.WriteBlock(infoBefore, 6);
		}

		auto inStream = std::make_unique<CFileInputStream>(FILE_NAME);
		auto decompressedStream = CDecryptedInputStream(std::move(inStream), 12);
		char infoAfter[6];

		REQUIRE(decompressedStream.ReadBlock(infoAfter, 6) == 6);
		REQUIRE(infoAfter[0] == infoBefore[0]);
		REQUIRE(infoAfter[1] == infoBefore[1]);
		REQUIRE(infoAfter[2] == infoBefore[2]);
		REQUIRE(infoAfter[3] == infoBefore[3]);
		REQUIRE(infoAfter[4] == infoBefore[4]);
		REQUIRE(infoAfter[5] == infoBefore[5]);
	}
}

TEST_CASE("check crypt and decrypt on memory stream")
{
	SECTION("writing by one byte")
	{
		std::vector<uint8_t> memory;
		{
			auto stream = std::make_unique<CMemoryOutputStream>(memory);
			auto encryptedStream = CEncryptedOutputStream(std::move(stream), 12);

			encryptedStream.WriteByte('1');
			encryptedStream.WriteByte('C');
			encryptedStream.WriteByte('C');
			encryptedStream.WriteByte('A');
			encryptedStream.WriteByte('A');
			encryptedStream.WriteByte('A');
			encryptedStream.WriteByte('\n');
			encryptedStream.WriteByte('A');
		}
		{
			auto inStream = std::make_unique<CMemoryInputStream>(memory);
			auto decryptedStream = CDecryptedInputStream(std::move(inStream), 12);

			REQUIRE(decryptedStream.ReadByte() == '1');
			REQUIRE(decryptedStream.ReadByte() == 'C');
			REQUIRE(decryptedStream.ReadByte() == 'C');
			REQUIRE(decryptedStream.ReadByte() == 'A');
			REQUIRE(decryptedStream.ReadByte() == 'A');
			REQUIRE(decryptedStream.ReadByte() == 'A');
			REQUIRE(decryptedStream.ReadByte() == '\n');
			REQUIRE(decryptedStream.ReadByte() == 'A');
		}
	}

	SECTION("writing by block")
	{
		char infoBefore[7] = {'1', 'C', 'C', 'A', 'A', 'A', '\n'};
		std::vector<uint8_t> memory;

		{
			auto stream = std::make_unique<CMemoryOutputStream>(memory);
			auto compressedStream = CEncryptedOutputStream(std::move(stream), 12);

			compressedStream.WriteBlock(infoBefore, 6);
		}

		auto inStream = std::make_unique<CMemoryInputStream>(memory);
		auto decompressedStream = CDecryptedInputStream(std::move(inStream), 12);
		char infoAfter[6];

		REQUIRE(decompressedStream.ReadBlock(infoAfter, 6) == 6);
		REQUIRE(infoAfter[0] == infoBefore[0]);
		REQUIRE(infoAfter[1] == infoBefore[1]);
		REQUIRE(infoAfter[2] == infoBefore[2]);
		REQUIRE(infoAfter[3] == infoBefore[3]);
		REQUIRE(infoAfter[4] == infoBefore[4]);
		REQUIRE(infoAfter[5] == infoBefore[5]);
	}
}