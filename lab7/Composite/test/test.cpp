#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Content/Group/CGroup/CGroup.h"
#include "../src/Content/Shape/CEllipse/CEllipse.h"
#include "../src/Content/Shape/CRectangle/CRectangle.h"
#include "../src/Content/Shape/CTriangle/CTriangle.h"

TEST_CASE("check throwing exceptions cases")
{
	CGroup group;
	GIVEN("empty group")
	{
		WHEN("ask count of shapes")
		{
			THEN("answer is 0")
			{
				REQUIRE(group.GetShapesCount() == 0);
			}
		}

		WHEN("add nullptr to second position")
		{
			THEN("exception")
			{
				REQUIRE_THROWS_AS(group.InsertShape(nullptr, 0), CEmptyShapeException);
			}
		}

		WHEN("add shape to second position")
		{
			auto rectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, 10, 20);

			THEN("exception")
			{
				REQUIRE_THROWS_AS(group.InsertShape(rectangle, 1), CWrongShapeIndexException);
			}
		}

		WHEN("remove shape from first position")
		{
			THEN("exception")
			{
				REQUIRE_THROWS_AS(group.RemoveShapeAtIndex(0), CWrongShapeIndexException);
			}
		}
	}
}

TEST_CASE("check adding items")
{
	CGroup group;

	GIVEN("empty group")
	{
		WHEN("ask count of shapes")
		{
			THEN("answer is 0")
			{
				REQUIRE(group.GetShapesCount() == 0);
			}
		}

		WHEN("add shape to first position")
		{
			auto rectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, 10, 20);
			group.InsertShape(rectangle, 0);

			THEN("shapes count will be 1")
			{
				REQUIRE(group.GetShapesCount() == 1);

				auto shape = group.GetShapeAtIndex(0)->GetFrame().value();

				REQUIRE(shape.width == 10);
				REQUIRE(shape.height == 20);
				REQUIRE(shape.leftTopPoint.x == 0);
				REQUIRE(shape.leftTopPoint.y == 0);
			}
		}

		WHEN("add shape to second position")
		{
			auto rectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, 10, 20);
			group.InsertShape(rectangle, 0);
			auto rectangle1 = std::make_shared<CRectangle>(PointD{ 10, 10 }, 20, 40);
			group.InsertShape(rectangle1, 0);

			REQUIRE(group.GetShapesCount() == 2);

			auto shape = group.GetShapeAtIndex(0)->GetFrame().value();

			REQUIRE(shape.width == 20);
			REQUIRE(shape.height == 40);
			REQUIRE(shape.leftTopPoint.x == 10);
			REQUIRE(shape.leftTopPoint.y == 10);
		}
	}
}

TEST_CASE("check deleting items")
{
	CGroup group;

	GIVEN("empty group")
	{
		WHEN("deleting shape from last position")
		{
			auto rectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, 10, 20);
			auto rectangle1 = std::make_shared<CRectangle>(PointD{ 10, 10 }, 110, 120);
			group.InsertShape(rectangle, 0);
			group.InsertShape(rectangle1, 1);

			THEN("first shape will be rectangle")
			{
				group.RemoveShapeAtIndex(group.GetShapesCount() - 1);
				REQUIRE(group.GetShapesCount() == 1);

				auto shape = group.GetShapeAtIndex(0)->GetFrame().value();

				REQUIRE(shape.width == 10);
				REQUIRE(shape.height == 20);
				REQUIRE(shape.leftTopPoint.x == 0);
				REQUIRE(shape.leftTopPoint.y == 0);
			}
		}

		WHEN("delete shape from first position")
		{
			auto rectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, 10, 20);
			auto rectangle1 = std::make_shared<CRectangle>(PointD{ 10, 10 }, 110, 120);
			group.InsertShape(rectangle, 0);
			group.InsertShape(rectangle1, 1);

			THEN("first shape will be rectangle1")
			{
				group.RemoveShapeAtIndex(0);
				REQUIRE(group.GetShapesCount() == 1);

				auto shape = group.GetShapeAtIndex(0)->GetFrame().value();

				REQUIRE(shape.width == 110);
				REQUIRE(shape.height == 120);
				REQUIRE(shape.leftTopPoint.x == 10);
				REQUIRE(shape.leftTopPoint.y == 10);
			}
		}

		WHEN("delete shape from center")
		{
			auto rectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, 10, 20);
			auto ellipse = std::make_shared<CEllipse>(PointD{ 10, 10 }, 110, 120);
			auto triangle = std::make_shared<CTriangle>(PointD{ 20, 20 }, PointD{ 210, 120 }, PointD{ 220, 230 });

			group.InsertShape(rectangle, 0);
			group.InsertShape(ellipse, 1);
			group.InsertShape(triangle, 2);

			THEN("at the second position will be triangle")
			{
				group.RemoveShapeAtIndex(1);
				REQUIRE(group.GetShapesCount() == 2);

				auto shape = group.GetShapeAtIndex(1)->GetFrame().value();

				REQUIRE(shape.width == 200);
				REQUIRE(shape.height == 210);
				REQUIRE(shape.leftTopPoint.x == 20);
				REQUIRE(shape.leftTopPoint.y == 20);
			}
		}
	}
}

TEST_CASE("add styles")
{
	CGroup group;

	GIVEN("group includes rectangle and ellipse with different styles")
	{
		auto rectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, 10, 20);
		rectangle->GetLineStyle()->SetColor(0x123456FF);
		rectangle->GetLineStyle()->SetThickness(3);
		rectangle->GetLineStyle()->Enable();
		rectangle->GetFillStyle()->SetColor(0x000000FF);
		rectangle->GetFillStyle()->Enable();

		auto ellipse = std::make_shared<CEllipse>(PointD{ 10, 10 }, 110, 120);
		ellipse->GetLineStyle()->SetColor(0x654321FF);
		ellipse->GetLineStyle()->SetThickness(4);
		ellipse->GetLineStyle()->Disable();
		ellipse->GetFillStyle()->SetColor(0xFFFFF000);

		group.InsertShape(rectangle, 0);
		group.InsertShape(ellipse, 0);

		WHEN("ask for group style")
		{
			THEN("params will be default values")
			{
				REQUIRE(group.GetFillStyle()->GetColor() == std::nullopt);
				REQUIRE(group.GetFillStyle()->isEnable() == false);
				REQUIRE(group.GetLineStyle()->isEnable() == false);
				REQUIRE(group.GetLineStyle()->GetColor() == std::nullopt);
				REQUIRE(group.GetLineStyle()->GetThickness() == std::nullopt);
			}
		}

		WHEN("set group style")
		{
			group.GetLineStyle()->SetThickness(2);
			group.GetLineStyle()->SetColor(0x123456FF);
			group.GetLineStyle()->Enable();

			group.GetFillStyle()->SetColor(0x654321FF);
			group.GetFillStyle()->Enable();

			THEN("group params will be the same")
			{
				REQUIRE(group.GetFillStyle()->GetColor().value() == 0x654321FF);
				REQUIRE(group.GetFillStyle()->isEnable() == true);
				REQUIRE(group.GetLineStyle()->isEnable() == true);
				REQUIRE(group.GetLineStyle()->GetColor().value() == 0x123456FF);
				REQUIRE(group.GetLineStyle()->GetThickness().value() == 2);
			}

			THEN("shapes params will be the same")
			{
				auto shape = group.GetShapeAtIndex(1);

				REQUIRE(shape->GetFillStyle()->GetColor().value() == 0x654321FF);
				REQUIRE(shape->GetFillStyle()->isEnable() == true);
				REQUIRE(shape->GetLineStyle()->isEnable() == true);
				REQUIRE(shape->GetLineStyle()->GetColor().value() == 0x123456FF);
				REQUIRE(shape->GetLineStyle()->GetThickness().value() == 2);
			}
		}
	}
}

TEST_CASE("test group frame")
{
	CGroup group;

	GIVEN("group includes rectangle and ellipse")
	{
		auto rectangle = std::make_shared<CRectangle>(PointD{ 2, 1 }, 3, 2);
		auto ellipse = std::make_shared<CEllipse>(PointD{ 5, 5 }, 2, 4);
		group.InsertShape(rectangle, 0);
		group.InsertShape(ellipse, 1);

		WHEN("get frame of group")
		{
			auto frame = group.GetFrame().value();

			THEN("frame will be right")
			{
				REQUIRE(frame.leftTopPoint.x == 2);
				REQUIRE(frame.leftTopPoint.y == 1);
				REQUIRE(frame.width == 5);
				REQUIRE(frame.height == 8);
			}
		}

		WHEN("resize and replace")
		{
			auto newFrame = FrameD{PointD{3, 2}, 10, 16};
			group.SetFrame(newFrame);
			auto frame = group.GetFrame().value();

			THEN("frame will be right")
			{
				REQUIRE(frame.leftTopPoint.x == 3);
				REQUIRE(frame.leftTopPoint.y == 2);
				REQUIRE(frame.width == 10);
				REQUIRE(frame.height == 16);
			}

			THEN("rectangle frame will be right")
			{
				auto shapesFrame = group.GetShapeAtIndex(0)->GetFrame().value();

				REQUIRE(shapesFrame.leftTopPoint.x == 3);
				REQUIRE(shapesFrame.leftTopPoint.y == 2);
				REQUIRE(shapesFrame.width == 6);
				REQUIRE(shapesFrame.height == 4);
			}

			THEN("ellipse frame will be right")
			{
				auto shapesFrame = group.GetShapeAtIndex(1)->GetFrame().value();

				REQUIRE(shapesFrame.leftTopPoint.x == 5);
				REQUIRE(shapesFrame.leftTopPoint.y == 2);
				REQUIRE(shapesFrame.width == 8);
				REQUIRE(shapesFrame.height == 16);
			}
		}
	}

	GIVEN("empty group and figure")
	{
		auto emptyGroup = std::make_shared<CGroup>();
		auto emptyEllipse = std::make_shared<CEllipse>(CEllipse({12, 12}, 0, 0));
		emptyGroup->InsertShape(emptyEllipse, 0);
		auto rectangle = std::make_shared<CRectangle>(CRectangle({12, 12}, 12, 12));

		group.InsertShape(emptyGroup, 0);
		group.InsertShape(rectangle, 0);

		WHEN("get frame of global group")
		{
			THEN("frame will be the same with rectangle")
			{
				auto frame = group.GetFrame().value();
				REQUIRE(frame.leftTopPoint.x == 12);
				REQUIRE(frame.leftTopPoint.y == 12);
				REQUIRE(frame.width == 12);
				REQUIRE(frame.height == 12);
			}
		}
	}
}