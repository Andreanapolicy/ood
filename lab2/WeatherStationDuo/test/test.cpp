#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../src/WeatherData/WeatherData.h"
#include "../src/Observer/Observer.h"

TEST_CASE("Observer two observable")
{
	std::ostringstream oss;

    CWeatherData weatherDataIn;
    CWeatherData weatherDataOut;

	CStatsDisplay display(weatherDataIn, weatherDataOut, oss);

	weatherDataIn.RegisterObserver(display, 0);
	weatherDataOut.RegisterObserver(display, 0);

	weatherDataIn.SetMeasurements(3, 0.7, 760);
	weatherDataOut.SetMeasurements(5, 0.24, 780);
	std::stringstream expectedString;

	expectedString << "Temperature: min: " + std::to_string(3.) + ", max: " + std::to_string(3.) + ", average: " + std::to_string(3.) + "\n"
					  "Humidity: min: " + std::to_string(0.7) + ", max: " + std::to_string(0.7) + ", average: " + std::to_string(0.7) + "\n"
					  "Pressure: min: " + std::to_string(760.) + ", max: " + std::to_string(760.) + ", average: " + std::to_string(760.) + "\n"
					  "Temperature: min: " + std::to_string(5.) + ", max: " + std::to_string(5.) + ", average: " + std::to_string(5.) + "\n"
				 	  "Humidity: min: " + std::to_string(0.24) + ", max: " + std::to_string(0.24) + ", average: " + std::to_string(0.24) + "\n"
				 	  "Pressure: min: " + std::to_string(780.) + ", max: " + std::to_string(780.) + ", average: " + std::to_string(780.) + "\n";

	REQUIRE(oss.str() == expectedString.str());

	weatherDataIn.SetMeasurements(10, 0.24, 751);
	weatherDataOut.SetMeasurements(2, 0.9, 720);

	expectedString << "Temperature: min: " + std::to_string(3.) + ", max: " + std::to_string(10.) + ", average: " + std::to_string(6.5) + "\n"
					  "Humidity: min: " + std::to_string(0.24) + ", max: " + std::to_string(0.7) + ", average: " + std::to_string(0.47) + "\n"
					  "Pressure: min: " + std::to_string(751.) + ", max: " + std::to_string(760.) + ", average: " + std::to_string(755.5) + "\n"
					  "Temperature: min: " + std::to_string(2.) + ", max: " + std::to_string(5.) + ", average: " + std::to_string(3.5) + "\n"
					  "Humidity: min: " + std::to_string(0.24) + ", max: " + std::to_string(0.9) + ", average: " + std::to_string(0.57) + "\n"
					  "Pressure: min: " + std::to_string(720.) + ", max: " + std::to_string(780.) + ", average: " + std::to_string(750.) + "\n";

	REQUIRE(oss.str() == expectedString.str());
}