cmake_minimum_required(VERSION 3.20)
project(SimUDuckFunc)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimUDuckFunc main.cpp src/Duck/CDecoyDuck src/Duck/CDuck src/Duck/CMallardDuck src/Duck/CModelDuck src/Duck/CRedheadDuck src/Duck/CRubberDuck include/Duck/CDecoyDuck include/Duck/CDuck include/Duck/CMallardDuck include/Duck/CModelDuck include/Duck/CRedheadDuck include/Duck/CRubberDuck include/FlyBehavior/FlyWithWings/FlyWithWings.h src/FlyBehavior/FlyWithWings/FlyWithWings.cpp include/FlyBehavior/FlyNoWay/FlyNoWay.h src/FlyBehavior/FlyNoWay/FlyNoWay.cpp include/DanceBehavior/MinuetBehavior/MinuetBehavior.h include/DanceBehavior/NoDanceBehavior/NoDanceBehavior.h include/DanceBehavior/WaltzBehavior/WaltzBehavior.h src/DanceBehavior/WaltzBehavior/WaltzBehavior.cpp src/DanceBehavior/NoDanceBehavior/NoDanceBehavior.cpp src/DanceBehavior/MinuetBehavior/MinuetBehavior.cpp include/QuackBehavior/MuteQuackBehavior/MuteQuackBehavior.h src/QuackBehavior/MuteQuackBehavior/MuteQuackBehavior.cpp include/QuackBehavior/QuackBehavior/QuackBehavior.h src/QuackBehavior/QuackBehavior/QuackBehavior.cpp include/QuackBehavior/SqueakBehavior/SqueakBehavior.h src/QuackBehavior/SqueakBehavior/SqueakBehavior.cpp)
#add_executable(SimUDuckFunc main.cpp src/ include/)
