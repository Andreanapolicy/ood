#include <iostream>
#include "src/WeatherData/WeatherData.h"

int main() {
	CWeatherData weatherData;

	CStatsDisplay display(std::cout);

	weatherData.RegisterObserver(display, 0);

	weatherData.SetMeasurements(3, 0.7, 760, 180, 2);
}
