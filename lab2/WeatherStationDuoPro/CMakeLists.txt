cmake_minimum_required(VERSION 3.20)
project(WeatherStationDuoPro)

set(CMAKE_CXX_STANDARD 17)

add_executable(WeatherStationDuoPro main.cpp src/Observer/Observer.h src/WeatherData/WeatherData.h)
add_executable(test test/test.cpp src/Observer/Observer.h src/WeatherData/WeatherData.h)