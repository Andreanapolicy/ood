cmake_minimum_required(VERSION 3.20)
project(Streams)

set(CMAKE_CXX_STANDARD 20)

add_executable(Streams main.cpp src/InputStream/InputStream.h src/OutputStream/OutputStream.h src/InputStream/InputStreamDecorator.h src/Series/Series.h src/OutputStream/OutputStreamDecorator.h)
add_executable(test test/test.cpp src/InputStream/InputStream.h src/OutputStream/OutputStream.h)
