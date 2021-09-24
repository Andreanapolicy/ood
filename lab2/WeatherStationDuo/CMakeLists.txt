cmake_minimum_required(VERSION 3.20)
project(WeatherStationDuo)

set(CMAKE_CXX_STANDARD 17)

add_executable(WeatherStation main.cpp src/Observer/Observer.h src/WeatherData/WeatherData.h)
add_executable(test test/test.cpp src/Observer/Observer.h src/WeatherData/WeatherData.h)