#include <iostream>
#include "src/WeatherData/WeatherData.h"

int main() {
	CWeatherData inWd;
	CWeatherData outWd;

	CStatsDisplay display(inWd, outWd, std::cout);
	inWd.RegisterObserver(display, 0);
	outWd.RegisterObserver(display, 1);

	inWd.SetMeasurements(3, 0.7, 760);
	outWd.SetMeasurements(5, 0.24, 780);
	inWd.SetMeasurements(10, 0.24, 751);
	outWd.SetMeasurements(2, 0.9, 720);
	return 0;
}
