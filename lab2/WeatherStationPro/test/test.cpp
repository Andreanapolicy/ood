#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/WeatherData/WeatherData.h"
#include "../src/Observer/Observer.h"

TEST_CASE("Check wind info")
{
	std::ostringstream oss;

    CWeatherData weatherData;

	CStatsDisplay display(oss);

	weatherData.RegisterObserver(display, 0);

	weatherData.SetMeasurements(3, 0.7, 760, 180, 2);
	std::stringstream expectedString;

	expectedString << "Temperature: min: " + std::to_string(3.) + ", max: " + std::to_string(3.) + ", average: " + std::to_string(3.) + "\n"
					  "Humidity: min: " + std::to_string(0.7) + ", max: " + std::to_string(0.7) + ", average: " + std::to_string(0.7) + "\n"
					  "Pressure: min: " + std::to_string(760.) + ", max: " + std::to_string(760.) + ", average: " + std::to_string(760.) + "\n"
					  "Wind: speed: min: " + std::to_string(2.) + ", max: " + std::to_string(2.) + ", average: " + std::to_string(2.) +
					  ", average direction: " + std::to_string(180.) + "\n";


	REQUIRE(oss.str() == expectedString.str());

	weatherData.SetMeasurements(10, 0.24, 751, 90, 9);

	expectedString << "Temperature: min: " + std::to_string(3.) + ", max: " + std::to_string(10.) + ", average: " + std::to_string(6.5) + "\n"
					  "Humidity: min: " + std::to_string(0.24) + ", max: " + std::to_string(0.7) + ", average: " + std::to_string(0.47) + "\n"
					  "Pressure: min: " + std::to_string(751.) + ", max: " + std::to_string(760.) + ", average: " + std::to_string(755.5) + "\n"
					  "Wind: speed: min: " + std::to_string(2.) + ", max: " + std::to_string(9.) + ", average: " + std::to_string(5.5) +
			          ", average direction: " + std::to_string(135.) + "\n";

	REQUIRE(oss.str() == expectedString.str());
}