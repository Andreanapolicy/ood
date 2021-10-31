#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/app/App.h"

TEST_CASE("check throwing exception on `draw line` without `begin draw`")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer modernGraphicsRenderer(oss);

	REQUIRE_THROWS(modernGraphicsRenderer.DrawLine({0, 0}, {1, 1}));
}

TEST_CASE("check throwing exception on `draw line` after `end draw`")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer modernGraphicsRenderer(oss);
	modernGraphicsRenderer.BeginDraw();
	REQUIRE_NOTHROW(modernGraphicsRenderer.DrawLine({0, 0}, {1, 1}));

	modernGraphicsRenderer.EndDraw();
	REQUIRE_THROWS(modernGraphicsRenderer.DrawLine({0, 0}, {1, 1}));
}

TEST_CASE("check drawing by adapter")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer modernGraphicsRenderer(oss);
	app::CModernGraphicsLibAdapter modernGraphicsLibAdapter(modernGraphicsRenderer);

	modernGraphicsRenderer.BeginDraw();

	modernGraphicsLibAdapter.MoveTo(0, 0);
	modernGraphicsLibAdapter.LineTo(12, 23);

	REQUIRE(oss.str() == "<draw>\n<line fromX=0 fromY=0 toX=12 toY=23/>\n");

	modernGraphicsRenderer.EndDraw();
	REQUIRE(oss.str() == "<draw>\n<line fromX=0 fromY=0 toX=12 toY=23/>\n</draw>\n");
}