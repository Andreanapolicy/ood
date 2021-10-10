#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Shape/CTriangle.h"
#include "../src/Shape/CRectangle.h"
#include "../src/Shape/CEllipse.h"
#include "../src/Shape/CRegularPolygon.h"
#include "../src/PictureDraft/CPictureDraft.h"

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

TEST_CASE("check picture draft")
{
	SECTION("standard settings")
	{
		CPictureDraft pictureDraft;
		REQUIRE(pictureDraft.GetShapesCount() == 0);
		REQUIRE_THROWS(pictureDraft.GetShape(0));
	}

	SECTION("creating picture draft with shapes")
	{
		CPictureDraft pictureDraft;

		CRegularPolygon regularPolygon(Color::Yellow, 4, { 12, 12 }, 12);
		auto regularPolygonPtr = std::make_unique<CRegularPolygon>(regularPolygon);

		CRectangle rectangle(Color::Yellow, { 12, 12 }, 4, 12);
		auto rectanglePtr = std::make_unique<CRectangle>(rectangle);

		WHEN("Adding regular polygon")
		{
			REQUIRE_NOTHROW(pictureDraft.AddShape(std::move(regularPolygonPtr)));
			REQUIRE_NOTHROW(pictureDraft.AddShape(std::move(rectanglePtr)));

			THEN("picture has 2 items")
			{
				REQUIRE(pictureDraft.GetShapesCount() == 2);
			}

			THEN("picture draft has regular polygon")
			{
				auto shape = dynamic_cast<CRegularPolygon&>(pictureDraft.GetShape(0));

				REQUIRE(shape.GetVertexCount() == 4);
				REQUIRE(shape.GetColor() == Color::Yellow);
				REQUIRE(shape.GetRadius() == 12);
				REQUIRE(shape.GetCenterPoint() == CPoint{12, 12});
			}
		}
	}
}