#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Shape/CTriangle.h"
#include "../src/Shape/CRectangle.h"
#include "../src/Shape/CEllipse.h"
#include "../src/Shape/CRegularPolygon.h"

TEST_CASE("Test triangle functional")
{
	CPoint firstVertex(12, 12);
	CPoint secondVertex(50, 12);
	CPoint thirdVertex(69, 36);

	CTriangle triangle(Color::Yellow, firstVertex, secondVertex, thirdVertex);

	THEN("triangle is yellow, with the same vertex")
	{
		REQUIRE(triangle.GetFirstVertex() == firstVertex);
		REQUIRE(triangle.GetSecondVertex() == secondVertex);
		REQUIRE(triangle.GetThirdVertex() == thirdVertex);
		REQUIRE(triangle.GetColor() == Color::Yellow);
	}
}

TEST_CASE("Test rectangle functional")
{
	CPoint topLeftVertex(12, 12);
	int width = 12;
	int height = 23;

	CRectangle rectangle(Color::Yellow, topLeftVertex, width, height);

	THEN("rectangle is yellow, with the same vertex")
	{
		REQUIRE(rectangle.GetTopLeftPoint() == topLeftVertex);
		REQUIRE(rectangle.GetWidth() == width);
		REQUIRE(rectangle.GetHeight() == height);
		REQUIRE(rectangle.GetColor() == Color::Yellow);
	}
}

TEST_CASE("Test ellipse functional")
{
	CPoint centerPoint(12, 12);
	int widthRadius = 12;
	int heightRadius = 23;

	CEllipse ellipse(Color::Yellow, centerPoint, widthRadius, heightRadius);

	THEN("ellipse is yellow, with the same vertex")
	{
		REQUIRE(ellipse.GetCenterPoint() == centerPoint);
		REQUIRE(ellipse.GetWidthRadius() == widthRadius);
		REQUIRE(ellipse.GetHeightRadius() == heightRadius);
		REQUIRE(ellipse.GetColor() == Color::Yellow);
	}
}

TEST_CASE("Test regular polygon functional")
{
	CPoint centerPoint(12, 12);
	int count = 12;
	int wrongCount = 2;
	int radius = 23;

	WHEN("create with 1 or 2 vertexes")
	{
		THEN("throwing exception")
		{
			REQUIRE_THROWS(CRegularPolygon(Color::Yellow, wrongCount, centerPoint, radius));
		}
	}

	CRegularPolygon regularPolygon(Color::Yellow, count, centerPoint, radius);

	THEN("regular polygon is yellow, with the same vertex")
	{
		REQUIRE(regularPolygon.GetCenterPoint() == centerPoint);
		REQUIRE(regularPolygon.GetRadius() == radius);
		REQUIRE(regularPolygon.GetVertexCount() == count);
		REQUIRE(regularPolygon.GetColor() == Color::Yellow);
	}
}