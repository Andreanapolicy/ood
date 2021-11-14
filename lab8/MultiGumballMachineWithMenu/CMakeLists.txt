cmake_minimum_required(VERSION 3.20)
project(MultiGumballMachineWithMenu)

set(CMAKE_CXX_STANDARD 20)

add_executable(MultiGumballMachineWithMenu main.cpp src/State/IState/IState.h src/GumballMachine/IGumballMachine/IGumballMachine.h src/State/CNoQuarterState/CNoQuarterState.h src/State/CHasQuarterState/CHasQuarterState.h src/State/CSoldState/CSoldState.h src/State/CSoldOutState/CSoldOutState.h src/GumballMachine/CGumballMachine/CGumballMachine.h src/State/CMaxQuarterCountState/CMaxQuarterCountState.h src/Menu/CMenu/CMenu.cpp src/Menu/CMenu/CMenu.h src/GumballMachineController/GumballMachineController.cpp src/GumballMachineController/GumballMachineController.h)
