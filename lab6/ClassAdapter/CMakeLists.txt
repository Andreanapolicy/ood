cmake_minimum_required(VERSION 3.20)
project(ClassAdapter)

set(CMAKE_CXX_STANDARD 20)

add_executable(ClassAdapter main.cpp src/app/App.h src/modern_graphics_lib/ModernGraphicsLib.h src/shape_drawing_lib/ShapeDrawingLib.h src/graphics_lib/GraphicsLib.h)
add_executable(Test test/test.cpp src/app/App.h src/modern_graphics_lib/ModernGraphicsLib.h src/shape_drawing_lib/ShapeDrawingLib.h src/graphics_lib/GraphicsLib.h)