#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Shape/CTriangle.h"
#include "../src/Shape/CRectangle.h"
#include "../src/Shape/CEllipse.h"
#include "../src/Shape/CRegularPolygon.h"
#include "../src/PictureDraft/CPictureDraft.h"
#include "../src/Canvas/TestCanvas.h"
#include "../src/Painter/CPainter.h"
#include "../src/ShapeFactory/CShapeFactory.h"
#include "../src/Designer/CDesigner.h"

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

TEST_CASE("check test canvas")
{
	TestCanvas testCanvas;
	CPictureDraft pictureDraft;

	WHEN("add regular polygon and draw")
	{
		CRegularPolygon regularPolygon(Color::Yellow, 4, { 12, 12 }, 12);
		auto regularPolygonPtr = std::make_unique<CRegularPolygon>(regularPolygon);
		pictureDraft.AddShape(std::move(regularPolygonPtr));

		CPainter::DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be regular polygon for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw line", "draw line", "draw line", "draw line"});
		}
	}

	WHEN("add rectangle and draw")
	{
		CRectangle rectangle(Color::Yellow, { 12, 12 }, 12, 12);
		auto rectanglePtr = std::make_unique<CRectangle>(rectangle);
		pictureDraft.AddShape(std::move(rectanglePtr));

		CPainter::DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be rectangle for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw line", "draw line", "draw line", "draw line"});
		}
	}

	WHEN("add ellipse and draw")
	{
		CEllipse ellipse(Color::Yellow, { 12, 12 }, 5, 12);
		auto ellipsePtr = std::make_unique<CEllipse>(ellipse);
		pictureDraft.AddShape(std::move(ellipsePtr));

		CPainter::DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be ellipse commands for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw ellipse"});
		}
	}

	WHEN("add ellipse, regular polygon and draw")
	{
		CEllipse ellipse(Color::Yellow, { 12, 12 }, 5, 12);
		auto ellipsePtr = std::make_unique<CEllipse>(ellipse);
		pictureDraft.AddShape(std::move(ellipsePtr));

		CRegularPolygon regularPolygon(Color::Yellow, 4, { 12, 12 }, 12);
		auto regularPolygonPtr = std::make_unique<CRegularPolygon>(regularPolygon);
		pictureDraft.AddShape(std::move(regularPolygonPtr));

		CPainter::DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be ellipse commands for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw ellipse", "set color", "draw line", "draw line", "draw line", "draw line"});
		}
	}
}

TEST_CASE("test designer")
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	std::stringstream ss;
	ss << "rectangle red 5 4 2 1" << std::endl << "ellipse pink 50 50 20 20";

	CPictureDraft pictureDraft = designer.CreateDraft(ss);

	REQUIRE(pictureDraft.GetShapesCount() == 2);
	auto testEllipse = dynamic_cast<CEllipse&>(pictureDraft.GetShape(1));

	REQUIRE(testEllipse.GetColor() == Color::Pink);
	REQUIRE(testEllipse.GetCenterPoint() == CPoint{50, 50});
	REQUIRE(testEllipse.GetHeightRadius() == 20);
	REQUIRE(testEllipse.GetWidthRadius() == 20);
}

TEST_CASE("test factory functionality")
{
	CShapeFactory shapeFactory;

	SECTION("check throwing exceptions")
	{
		REQUIRE_THROWS(shapeFactory.CreateShape(""));
		REQUIRE_THROWS(shapeFactory.CreateShape("triangke"));
		REQUIRE_THROWS(shapeFactory.CreateShape("triangle 10 20 15 00 30 40"));
	}

	SECTION("create ellipse")
	{
		auto shape = shapeFactory.CreateShape("ellipse red 12 12 12 12");

		CEllipse ellipse = dynamic_cast<CEllipse&>(*shape.get());

		REQUIRE(ellipse.GetColor() == Color::Red);
		REQUIRE(ellipse.GetCenterPoint() == CPoint{12, 12});
		REQUIRE(ellipse.GetWidthRadius() == 12);
		REQUIRE(ellipse.GetHeightRadius() == 12);
	}

	SECTION("create rectangle")
	{
		auto shape = shapeFactory.CreateShape("rectangle red 12 12 12 12");

		CRectangle rectangle = dynamic_cast<CRectangle&>(*shape.get());

		REQUIRE(rectangle.GetColor() == Color::Red);
		REQUIRE(rectangle.GetTopLeftPoint() == CPoint{12, 12});
		REQUIRE(rectangle.GetWidth() == 12);
		REQUIRE(rectangle.GetHeight() == 12);
	}

	SECTION("create triangle")
	{
		auto shape = shapeFactory.CreateShape("triangle red 12 12 12 12 12 12");

		CTriangle triangle = dynamic_cast<CTriangle&>(*shape.get());

		REQUIRE(triangle.GetColor() == Color::Red);
		REQUIRE(triangle.GetFirstVertex() == CPoint{12, 12});
		REQUIRE(triangle.GetSecondVertex() == CPoint{12, 12});
		REQUIRE(triangle.GetThirdVertex() == CPoint{12, 12});
	}

	SECTION("create regular polygon")
	{
		auto shape = shapeFactory.CreateShape("regular_polygon red 12 12 12 12");

		CRegularPolygon regularPolygon = dynamic_cast<CRegularPolygon&>(*shape.get());

		REQUIRE(regularPolygon.GetColor() == Color::Red);
		REQUIRE(regularPolygon.GetCenterPoint() == CPoint{12, 12});
		REQUIRE(regularPolygon.GetRadius() == 12);
		REQUIRE(regularPolygon.GetVertexCount() == 12);
	}
}