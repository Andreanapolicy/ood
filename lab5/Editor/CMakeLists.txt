cmake_minimum_required(VERSION 3.20)
project(Editor)

set(CMAKE_CXX_STANDARD 20)

add_executable(Editor main.cpp src/Content/IImage/IImage.h src/Content/CImage/CImage.h src/Content/CImage/CImage.cpp src/Content/Exception/ImageDoesNotExistException.h src/Content/Exception/WrongImageSizeException.h test/test.cpp)
add_executable(Tests test/test.cpp src/Content/IImage/IImage.h src/Content/CImage/CImage.h src/Content/CImage/CImage.cpp src/Content/Exception/ImageDoesNotExistException.h src/Content/Exception/WrongImageSizeException.h)
