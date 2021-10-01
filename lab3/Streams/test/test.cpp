#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/InputStream/InputStream.h"

TEST_CASE("check file input stream")
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
			THEN("there is no throws")
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
		}
	}
}