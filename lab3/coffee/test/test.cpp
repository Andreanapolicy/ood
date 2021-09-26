#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Beverage/Beverages.h"
#include "../src/Condiments/Condiments.h"

TEST_CASE("check coffee cost")
{
	GIVEN("latte with standard portion")
	{
		CLatte latte = CLatte(CoffeePortion::Standard);

		REQUIRE(latte.GetDescription() == "Standard Latte");
		REQUIRE(latte.GetCost() == 90);
	}

	GIVEN("latte with double portion")
	{
		CLatte latte = CLatte(CoffeePortion::Double);

		REQUIRE(latte.GetDescription() == "Double Latte");
		REQUIRE(latte.GetCost() == 130);
	}

	GIVEN("cappuccino with standard portion")
	{
		CCappuccino cappuccino = CCappuccino(CoffeePortion::Standard);

		REQUIRE(cappuccino.GetDescription() == "Standard Cappuccino");
		REQUIRE(cappuccino.GetCost() == 80);
	}

	GIVEN("cappuccino with double portion")
	{
		CCappuccino cappuccino = CCappuccino(CoffeePortion::Double);

		REQUIRE(cappuccino.GetDescription() == "Double Cappuccino");
		REQUIRE(cappuccino.GetCost() == 120);
	}
}

TEST_CASE("check tea cost")
{
	GIVEN("white tea")
	{
		CTea tea = CTea(TeaType::White);

		REQUIRE(tea.GetDescription() == "White Tea");
		REQUIRE(tea.GetCost() == 30);
	}

	GIVEN("black tea")
	{
		CTea tea = CTea(TeaType::Black);

		REQUIRE(tea.GetDescription() == "Black Tea");
		REQUIRE(tea.GetCost() == 30);
	}

	GIVEN("green tea")
	{
		CTea tea = CTea(TeaType::Green);

		REQUIRE(tea.GetDescription() == "Green Tea");
		REQUIRE(tea.GetCost() == 30);
	}

	GIVEN("yellow tea")
	{
		CTea tea = CTea(TeaType::Yellow);

		REQUIRE(tea.GetDescription() == "Yellow Tea");
		REQUIRE(tea.GetCost() == 30);
	}
}

TEST_CASE("check milkshake cost")
{
	GIVEN("small milkshake")
	{
		CMilkshake milkshake = CMilkshake(MilkshakePortion::Small);

		REQUIRE(milkshake.GetDescription() == "Small Milkshake");
		REQUIRE(milkshake.GetCost() == 50);
	}

	GIVEN("medium milkshake")
	{
		CMilkshake milkshake = CMilkshake(MilkshakePortion::Medium);

		REQUIRE(milkshake.GetDescription() == "Medium Milkshake");
		REQUIRE(milkshake.GetCost() == 60);
	}

	GIVEN("big milkshake")
	{
		CMilkshake milkshake = CMilkshake(MilkshakePortion::Big);

		REQUIRE(milkshake.GetDescription() == "Big Milkshake");
		REQUIRE(milkshake.GetCost() == 80);
	}
}

TEST_CASE("check condiment on Latte")
{
	GIVEN("Double latte")
	{
		CLatte latte = CLatte(CoffeePortion::Double);

		WHEN("add cream with nut liquor")
		{
			auto latte = std::make_unique<CLatte>(CoffeePortion::Double);
			auto latteWithCream = std::make_unique<CCream>(std::move(latte));
			auto latteWithCreamAndWithNutLiquor = std::make_unique<CLiquor>(std::move(latteWithCream), LiquorType::Nut);

			REQUIRE(latteWithCreamAndWithNutLiquor->GetDescription() == "Double Latte, Cream, Liquor with nut");
			REQUIRE(latteWithCreamAndWithNutLiquor->GetCost() == 205);
		}
	}

	GIVEN("Standard latte")
	{
		CLatte latte = CLatte(CoffeePortion::Double);

		WHEN("add 10 slice of chocolate")
		{
			auto latte = std::make_unique<CLatte>(CoffeePortion::Standard);
			auto latteWithChocolate = std::make_unique<CChocolate>(std::move(latte), 10);

			THEN("where are only 5 slice of chocolate")
			{
				REQUIRE(latteWithChocolate->GetDescription() == "Standard Latte, Chocolate slice(5)");
				REQUIRE(latteWithChocolate->GetCost() == 140);
			}
		}
	}
}