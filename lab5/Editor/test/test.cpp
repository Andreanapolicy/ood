#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Content/CImage/CImage.h"

TEST_CASE("check creation image")
{
	SECTION("construction with exceptions(wrong extention)")
	{
		REQUIRE_THROWS_AS(CImage("hello.js", 200, 200), ImageDoesNotExistException);
	}

	SECTION("construction with exceptions(file does not exist)")
	{
		REQUIRE_THROWS_AS(CImage("hello.png", 200, 200), ImageDoesNotExistException);
	}

	SECTION("construction with exceptions(wrong size)")
	{
		REQUIRE_THROWS_AS(CImage("../test/image.png", 0, 200), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 200, -1), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 200, 20000), WrongImageSizeException);
		REQUIRE_THROWS_AS(CImage("../test/image.png", 20000, 200), WrongImageSizeException);
	}

	SECTION("create image without exceptions")
	{
		CImage image("../test/image.png", 200, 350);

		THEN("Getters have to get right values")
		{
			REQUIRE(image.GetWidth() == 200);
			REQUIRE(image.GetHeight() == 350);
			REQUIRE_NOTHROW(image.GetPath());
		}
	}
}