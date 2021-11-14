#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/GumballMachine/CGumballMachine/CGumballMachine.h"

std::string GetState(unsigned int ballCount, unsigned int quarterCount, const std::string &state)
{
    return "Best C++ gumball Machine\nGumballs count: " + std::to_string(ballCount) + "\nQuarters count: " +
           std::to_string(quarterCount) + "\nMachine state: " + state;
}

TEST_CASE("Sold out state cases")
{
    GIVEN("empty gumball machine")
    {
        CGumballMachine gumballMachine(0);
        REQUIRE(gumballMachine.ToString() == GetState(0, 0, "sold out"));

        WHEN("try to insert quarter")
        {
            gumballMachine.InsertQuarter();

            THEN("can't insert, because all gumballs sold out")
            {
                REQUIRE(gumballMachine.ToString() == GetState(0, 0, "sold out"));
            }
        }

        WHEN("try to eject quarter")
        {
            gumballMachine.EjectQuarter();

            THEN("can't eject, quarter not inserted")
            {
                REQUIRE(gumballMachine.ToString() == GetState(0, 0, "sold out"));
            }
        }

        WHEN("try to turn crank")
        {
            gumballMachine.TurnCrank();

            THEN("can't turn crank, quarter not inserted")
            {
                REQUIRE(gumballMachine.ToString() == GetState(0, 0, "sold out"));
            }
        }

        WHEN("try to add gumballs")
        {
            gumballMachine.InsertBalls(2);

            THEN("gumball machine with 2 gumballs")
            {
                REQUIRE(gumballMachine.ToString() == GetState(2, 0, "waiting for quarter"));
            }
        }

        WHEN("try to add 0 gumballs")
        {
            gumballMachine.InsertBalls(0);

            THEN("gumball machine with 0 gumballs")
            {
                REQUIRE(gumballMachine.ToString() == GetState(0, 0, "sold out"));
            }
        }
    }

    GIVEN("gumball machine with 1 gumball")
    {
        CGumballMachine gumballMachine(1);
        REQUIRE(gumballMachine.ToString() == GetState(1, 0, "waiting for quarter"));

        WHEN("by 1 gumball")
        {
            gumballMachine.InsertQuarter();
            gumballMachine.TurnCrank();

            THEN("gumball machine will be empty after delivering")
            {
                REQUIRE(gumballMachine.ToString() == GetState(0, 0, "sold out"));
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
        REQUIRE(gumballMachine.ToString() == GetState(3, 1, "waiting for turning the crank"));

        WHEN("try to insert quarter")
        {
            gumballMachine.InsertQuarter();

            THEN("inserted 2 quarters")
            {
                REQUIRE(gumballMachine.ToString() == GetState(3, 2, "waiting for turning the crank"));
            }
        }

        WHEN("try to eject quarter")
        {
            gumballMachine.EjectQuarter();

            THEN("quarters will be ejected")
            {
                REQUIRE(gumballMachine.ToString() == GetState(3, 0, "waiting for quarter"));
            }
        }

        WHEN("try to turn crank")
        {
            gumballMachine.TurnCrank();

            THEN("gumball will be delivered")
            {
                REQUIRE(gumballMachine.ToString() == GetState(2, 0, "waiting for quarter"));
            }
        }

        WHEN("try to add gumballs")
        {
            gumballMachine.InsertBalls(2);

            THEN("gumball machine with 5 gumballs")
            {
                REQUIRE(gumballMachine.ToString() == GetState(5, 1, "waiting for turning the crank"));
            }
        }
    }
}

TEST_CASE("No quarter state cases")
{
    GIVEN("gumball machine with 3 gum")
    {
        CGumballMachine gumballMachine(3);
        REQUIRE(gumballMachine.ToString() == GetState(3, 0, "waiting for quarter"));

        WHEN("try to insert quarter")
        {
            gumballMachine.InsertQuarter();

            THEN("quarter will be inserted")
            {
                REQUIRE(gumballMachine.ToString() == GetState(3, 1, "waiting for turning the crank"));
            }
        }

        WHEN("try to eject quarter")
        {
            gumballMachine.EjectQuarter();

            THEN("quarter won't be ejected")
            {
                REQUIRE(gumballMachine.ToString() == GetState(3, 0, "waiting for quarter"));
            }
        }

        WHEN("try to turn crank")
        {
            gumballMachine.TurnCrank();

            THEN("gumball won't be delivered")
            {
                REQUIRE(gumballMachine.ToString() == GetState(3, 0, "waiting for quarter"));
            }
        }

        WHEN("try to add gumballs")
        {
            gumballMachine.InsertBalls(2);

            THEN("gumball machine with 2 gumballs")
            {
                REQUIRE(gumballMachine.ToString() == GetState(5, 0, "waiting for quarter"));
            }
        }
    }
}

TEST_CASE("test max quarters state cases")
{
    GIVEN("gumball machine with 4 gumballs and 5 coins")
    {
        CGumballMachine gumballMachine(4);
        gumballMachine.InsertQuarter();
        gumballMachine.InsertQuarter();
        gumballMachine.InsertQuarter();
        gumballMachine.InsertQuarter();
        gumballMachine.InsertQuarter();

        REQUIRE(gumballMachine.ToString() == GetState(4, 5, "Quarters count is full. Waiting for turning the crank"));

        WHEN("try to insert quarter")
        {
            gumballMachine.InsertQuarter();

            THEN("quarter won't be inserted")
            {
                REQUIRE(gumballMachine.ToString() == GetState(4, 5, "Quarters count is full. Waiting for turning the crank"));
            }
        }

        WHEN("try to add gumballs")
        {
            gumballMachine.InsertBalls(2);

            THEN("gumball machine with 2 gumballs")
            {
                REQUIRE(gumballMachine.ToString() == GetState(6, 5, "Quarters count is full. Waiting for turning the crank"));
            }
        }

        WHEN("try to eject quarter")
        {
            gumballMachine.EjectQuarter();

            THEN("quarters will be ejected")
            {
                REQUIRE(gumballMachine.ToString() == GetState(4, 0, "waiting for quarter"));
            }
        }

        WHEN("try to turn crank")
        {
            gumballMachine.TurnCrank();

            THEN("gumball will be delivered")
            {
                REQUIRE(gumballMachine.ToString() == GetState(3, 4, "waiting for turning the crank"));
            }
        }

        WHEN("try to get 5 gumballs")
        {
            gumballMachine.TurnCrank();
            gumballMachine.TurnCrank();
            gumballMachine.TurnCrank();
            gumballMachine.TurnCrank();
            gumballMachine.TurnCrank();

            THEN("all gumballs will be sold out")
            {
                REQUIRE(gumballMachine.ToString() == GetState(0, 1, "sold out"));
            }
        }
    }
}