cmake_minimum_required(VERSION 3.20)
project(Composite)

set(CMAKE_CXX_STANDARD 20)

add_executable(Composite main.cpp src/Content/Shape/IShape/IShape.h src/Content/Group/IGroup/IGroup.h src/Content/Style/IStyle/IStyle.h src/Common/Frame/Frame.h src/Common/Point/Point.h src/Common/Color/Color.h src/Content/Shape/IDrawable/IDrawable.h src/Content/Shape/CRectangle/CRectangle.cpp src/Content/Shape/CRectangle/CRectangle.h src/Content/Shape/CShape/CShape.cpp src/Content/Shape/CShape/CShape.h src/Content/Style/IBorderStyle/IBorderStyle.h src/Content/Style/CBorderStyle/CBorderStyle.cpp src/Content/Style/CBorderStyle/CBorderStyle.h src/Content/Style/CFillStyle/CFillStyle.cpp src/Content/Style/CFillStyle/CFillStyle.h)
