cmake_minimum_required(VERSION 3.20)
project(NativeMultiGumballMachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(NativeMultiGumballMachine main.cpp src/GumballMachine/CGumballMachine/CGumballMachine.h)
add_executable(Tests test/test.cpp)
