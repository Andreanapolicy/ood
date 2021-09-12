cmake_minimum_required(VERSION 3.20)
project(SimUDuck)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimUDuck main.cpp include/FlyBehavior/IFlyBehavior/IFlyBehavior.h include/FlyBehavior/CFlyWithWings/CFlyWithWings.h src/FlyBehavior/CFlyWithWings/CFlyWithWings.cpp include/FlyBehavior/CFlyNoWay/CFlyNoWay.h src/FlyBehavior/CFlyNoWay/CFlyNoWay.cpp include/QuackBehavior/IQuackBehavior/IQuackBehavior.h include/QuackBehavior/CQuackBehavior/CQuackBehavior.h src/QuackBehavior/CQuackBehavior/CQuackBehavior.cpp include/QuackBehavior/CSqueakBehavior/CSqueakBehavior.h src/QuackBehavior/CSqueakBehavior/CSqueakBehavior.cpp include/QuackBehavior/CMuteQuackBehavior/CMuteQuackBehavior.h src/QuackBehavior/CMuteQuackBehavior/CMuteQuackBehavior.cpp include/Duck/CDuck/CDuck.h src/Duck/CDuck/CDuck.cpp include/Duck/CMallardDuck/CMallardDuck.h src/Duck/CMallardDuck/CMallardDuck.cpp src/Duck/CRedheadDuck/CRedheadDuck.cpp include/Duck/CDecoyDuck/CDecoyDuck.h src/Duck/CDecoyDuck/CDecoyDuck.cpp src/Duck/CRubberDuck/CRubberDuck.cpp include/Duck/CRubberDuck/CRubberDuck.h include/Duck/CModelDuck/CModelDuck.h src/Duck/CModelDuck/CModelDuck.cpp)
