#pragma once
#include "../../../Common/Color/Color.h"
#include "../../../Common/Point/Point.h"
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(PointD from, PointD to, Color borderColor = 0, double thickness = 0) = 0;

	virtual void FillPolygon(const std::vector<PointD>& points, Color fillColor) = 0;

	virtual void DrawEllipse(PointD center, double widthRadius, double heightRadius, Color fillColor = 0, Color borderColor = 0, double thickness = 0) = 0;

	virtual ~ICanvas() = default;
};