cmake_minimum_required(VERSION 3.20)
project(WeatherStation)

set(CMAKE_CXX_STANDARD 17)

add_executable(WeatherStation main.cpp src/Observer/IObserver/IObserver.h src/Observer/IObservable/IObservable.h src/Observer/CObservable/CObservable.h src/WeatherData/CDisplay/CDisplay.h src/WeatherData/SWeatherInfo/SWeatherInfo.h src/WeatherData/CDisplay/CDisplay.cpp src/WeatherData/CStatsDisplay/CStatsDisplay.cpp src/WeatherData/CStatsDisplay/CStatsDisplay.h src/WeatherData/CStatisticData/CStatisticData.cpp src/WeatherData/CStatisticData/CStatisticData.h src/WeatherData/CWeatherData/CWeatherData.cpp src/WeatherData/CWeatherData/CWeatherData.h)
