#include "./src/WeatherData/CWeatherData/CWeatherData.h"
#include "./src/WeatherData/CDisplay/CDisplay.h"
#include "./src/WeatherData/CStatsDisplay/CStatsDisplay.h"

int main()
{
	CWeatherData weatherData;

	CDisplay display;
	weatherData.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	weatherData.RegisterObserver(statsDisplay, 0);

	weatherData.SetMeasurements(3, 0.7, 760);
	weatherData.SetMeasurements(4, 0.8, 761);

	weatherData.RemoveObserver(statsDisplay);

	weatherData.SetMeasurements(10, 0.8, 761);
	weatherData.SetMeasurements(-10, 0.8, 761);

	return 0;
}