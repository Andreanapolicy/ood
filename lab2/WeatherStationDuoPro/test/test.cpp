#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/WeatherData/WeatherData.h"

TEST_CASE("Check wind info with in and out data")
{
	std::ostringstream oss;
    CWeatherData weatherData;
    CWeatherDataPro weatherDataPro;
	CStatsDisplay display(weatherData, weatherDataPro, oss);

	weatherData.RegisterObserver(display, 0);
	weatherDataPro.RegisterObserver(display, 0);

	weatherData.SetMeasurements(3, 0.7, 760);
	weatherDataPro.SetMeasurements(3, 0.7, 760, 180, 2);

	std::stringstream expectedString;

	expectedString << "Temperature: min: " + std::to_string(3.) + ", max: " + std::to_string(3.) + ", average: " + std::to_string(3.) + "\n"
					  "Humidity: min: " + std::to_string(0.7) + ", max: " + std::to_string(0.7) + ", average: " + std::to_string(0.7) + "\n"
					  "Pressure: min: " + std::to_string(760.) + ", max: " + std::to_string(760.) + ", average: " + std::to_string(760.) + "\n"
                      "Temperature: min: " + std::to_string(3.) + ", max: " + std::to_string(3.) + ", average: " + std::to_string(3.) + "\n"
                      "Humidity: min: " + std::to_string(0.7) + ", max: " + std::to_string(0.7) + ", average: " + std::to_string(0.7) + "\n"
                      "Pressure: min: " + std::to_string(760.) + ", max: " + std::to_string(760.) + ", average: " + std::to_string(760.) + "\n"
					  "Wind: speed: min: " + std::to_string(2.) + ", max: " + std::to_string(2.) + ", average: " + std::to_string(2.) +
					  ", average direction: " + std::to_string(180.) + "\n";

	REQUIRE(oss.str() == expectedString.str());

    weatherData.SetMeasurements(9, 0.24, 780);
    weatherDataPro.SetMeasurements(5, 0.32, 750, 190, 9);

    expectedString << "Temperature: min: " + std::to_string(3.) + ", max: " + std::to_string(9.) + ", average: " + std::to_string(6.) + "\n"
                      "Humidity: min: " + std::to_string(0.24) + ", max: " + std::to_string(0.7) + ", average: " + std::to_string(0.47) + "\n"
                      "Pressure: min: " + std::to_string(760.) + ", max: " + std::to_string(780.) + ", average: " + std::to_string(770.) + "\n"
                      "Temperature: min: " + std::to_string(3.) + ", max: " + std::to_string(5.) + ", average: " + std::to_string(4.) + "\n"
                      "Humidity: min: " + std::to_string(0.32) + ", max: " + std::to_string(0.7) + ", average: " + std::to_string(0.51) + "\n"
                      "Pressure: min: " + std::to_string(750.) + ", max: " + std::to_string(760.) + ", average: " + std::to_string(755.) + "\n"
                      "Wind: speed: min: " + std::to_string(2.) + ", max: " + std::to_string(9.) + ", average: " + std::to_string(5.5) +
                      ", average direction: " + std::to_string(185.) + "\n";
	REQUIRE(oss.str() == expectedString.str());
}