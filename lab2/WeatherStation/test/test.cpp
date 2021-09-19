#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/Observer/CPriorityTestObserver/CPriorityTestObserver.h"
#include "../src/Observer/CDestructionTestObserver/CDestructionTestObserver.h"
#include "../src/WeatherData/CWeatherData/CWeatherData.h"

TEST_CASE("check priority observer")
{
	std::ostringstream oss;
	CWeatherData weatherData;

	CPriorityTestObserver firstObserver(1, oss);
	CPriorityTestObserver secondObserver(2, oss);
	CPriorityTestObserver thirdObserver(3, oss);
	CPriorityTestObserver fourthObserver(4, oss);

	weatherData.RegisterObserver(firstObserver, 2);
	weatherData.RegisterObserver(secondObserver, 0);
	weatherData.RegisterObserver(thirdObserver, 1);
	weatherData.RegisterObserver(fourthObserver, 3);

	weatherData.SetMeasurements(10, 10, 720);

	REQUIRE(oss.str() == "2314");
}

TEST_CASE("check destruction observer while updating")
{
	CWeatherData weatherData;
	CDestructionTestObserver destructionTestObserver(weatherData);

	weatherData.RegisterObserver(destructionTestObserver, 0);
	weatherData.SetMeasurements(0, 0, 770);
}