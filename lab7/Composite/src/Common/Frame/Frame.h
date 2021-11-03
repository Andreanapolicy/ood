#pragma once
#include "../Point/Point.h"

template<typename T>
struct Frame
{
	Point<T> leftTopPoint;
	T width;
	T height;
};

typedef Frame<double> FrameD;