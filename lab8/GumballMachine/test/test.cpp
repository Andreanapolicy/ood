#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/GumballMachine/CGamballMachine/CGamballMachine.h"

std::string GetState(unsigned int count, const std::string& state)
{
	return "Best C++ gumball Machine\nGumballs count: " + std::to_string(count) + "\nMachine state: " + state;
}

TEST_CASE("Sold out state cases")
{
	GIVEN("empty gumball machine")
	{
		CGumballMachine gumballMachine(0);
		REQUIRE(gumballMachine.ToString() == GetState(0, "sold out"));

		WHEN("try to insert quarter")
		{
			gumballMachine.InsertQuarter();

			THEN("can't insert, because all gumballs sold out")
			{
				REQUIRE(gumballMachine.ToString() == GetState(0, "sold out"));
			}
		}

		WHEN("try to eject quarter")
		{
			gumballMachine.EjectQuarter();

			THEN("can't eject, quarter not inserted")
			{
				REQUIRE(gumballMachine.ToString() == GetState(0, "sold out"));
			}
		}

		WHEN("try to turn crank")
		{
			gumballMachine.TurnCrank();

			THEN("can't turn crank, quarter not inserted")
			{
				REQUIRE(gumballMachine.ToString() == GetState(0, "sold out"));
			}
		}
	}

	GIVEN("gumball machine with 1 gumball")
	{
		CGumballMachine gumballMachine(1);
		REQUIRE(gumballMachine.ToString() == GetState(1, "waiting for quarter"));

		WHEN("by 1 gumball")
		{
			gumballMachine.InsertQuarter();
			gumballMachine.TurnCrank();

			THEN("gumball machine will be empty after delivering")
			{
				REQUIRE(gumballMachine.ToString() == GetState(0, "sold out"));
			}
		}
	}
}

TEST_CASE("Has quarter state cases")
{
	GIVEN("gumball machine with 3 gum")
	{
		CGumballMachine gumballMachine(3);
		gumballMachine.InsertQuarter();
		REQUIRE(gumballMachine.ToString() == GetState(3, "waiting for turning the crank"));

		WHEN("try to insert quarter")
		{
			gumballMachine.InsertQuarter();

			THEN("quarter already inserted")
			{
				REQUIRE(gumballMachine.ToString() == GetState(3, "waiting for turning the crank"));
			}
		}

		WHEN("try to eject quarter")
		{
			gumballMachine.EjectQuarter();

			THEN("quarter will be ejected")
			{
				REQUIRE(gumballMachine.ToString() == GetState(3, "waiting for quarter"));
			}
		}

		WHEN("try to turn crank")
		{
			gumballMachine.TurnCrank();

			THEN("gumball will be delivered")
			{
				REQUIRE(gumballMachine.ToString() == GetState(2, "waiting for quarter"));
			}
		}
	}
}

TEST_CASE("No quarter state cases")
{
	GIVEN("gumball machine with 3 gum")
	{
		CGumballMachine gumballMachine(3);
		REQUIRE(gumballMachine.ToString() == GetState(3, "waiting for quarter"));

		WHEN("try to insert quarter")
		{
			gumballMachine.InsertQuarter();

			THEN("quarter will be inserted")
			{
				REQUIRE(gumballMachine.ToString() == GetState(3, "waiting for turning the crank"));
			}
		}

		WHEN("try to eject quarter")
		{
			gumballMachine.EjectQuarter();

			THEN("quarter won't be ejected")
			{
				REQUIRE(gumballMachine.ToString() == GetState(3, "waiting for quarter"));
			}
		}

		WHEN("try to turn crank")
		{
			gumballMachine.TurnCrank();

			THEN("gumball won't be delivered")
			{
				REQUIRE(gumballMachine.ToString() == GetState(3, "waiting for quarter"));
			}
		}
	}
}