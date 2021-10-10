cmake_minimum_required(VERSION 3.20)
project(Shapes)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Shapes main.cpp src/ShapeFactory/IShapeFactory.h src/Color/Color.h src/Shape/CShape.h src/Shape/CTriangle.h src/Point/CPoint.h src/Canvas/ICanvas.h src/Shape/CRectangle.h src/Shape/CEllipse.h src/Shape/CRegularPolygon.h src/Shape/Exception/InvalidVertexCountException.h src/PictureDraft/CPictureDraft.h src/PictureDraft/Exception/ShapesIndexOutOfRange.h src/Designer/CDesigner.h src/Designer/IDesigner.h src/ShapeFactory/CShapeFactory.h src/Painter/CPainter.h src/Canvas/CCanvas.h src/ShapeFactory/Exception/InvalidParamsCountException.h src/ShapeFactory/Exception/InvalidNameOfShapeException.h src/ShapeFactory/Exception/InvalidParamException.h src/Canvas/TestCanvas.h)
add_executable(Tests test/test.cpp src/ShapeFactory/IShapeFactory.h src/Color/Color.h src/Shape/CShape.h src/Shape/CTriangle.h src/Point/CPoint.h src/Canvas/ICanvas.h src/Shape/CRectangle.h src/Shape/CEllipse.h src/Shape/CRegularPolygon.h src/Shape/Exception/InvalidVertexCountException.h src/PictureDraft/CPictureDraft.h src/PictureDraft/Exception/ShapesIndexOutOfRange.h)

target_link_libraries(Shapes sfml-graphics sfml-audio sfml-window)
target_link_libraries(Tests sfml-graphics sfml-audio sfml-window)
