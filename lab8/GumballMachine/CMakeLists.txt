cmake_minimum_required(VERSION 3.20)
project(GumballMachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(GumballMachine main.cpp src/State/IState/IState.h src/GumballMachine/IGumballMachine/IGumballMachine.h src/State/CNoQuarterState/CNoQuarterState.h src/State/CHasQuarterState/CHasQuarterState.h src/State/CSoldState/CSoldState.h src/State/CSoldOutState/CSoldOutState.h src/GumballMachine/CGamballMachine/CGamballMachine.h test/test.cpp)
add_executable(Test test/test.cpp src/State/IState/IState.h src/GumballMachine/IGumballMachine/IGumballMachine.h src/State/CNoQuarterState/CNoQuarterState.h src/State/CHasQuarterState/CHasQuarterState.h src/State/CSoldState/CSoldState.h src/State/CSoldOutState/CSoldOutState.h src/GumballMachine/CGamballMachine/CGamballMachine.h)
