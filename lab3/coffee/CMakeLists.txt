cmake_minimum_required(VERSION 3.20)
project(coffee)

set(CMAKE_CXX_STANDARD 20)

add_executable(coffee main.cpp src/Beverage/IBeverage.h src/Beverage/Beverages.h src/Condiments/Condiments.h)

add_executable(test test/test.cpp src/Beverage/IBeverage.h src/Beverage/Beverages.h src/Condiments/Condiments.h)