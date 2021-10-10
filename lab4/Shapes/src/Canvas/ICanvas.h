#pragma once
#include "../Point/CPoint.h"
#include "../Color/Color.h"

class ICanvas
{
public:
	virtual void SetColor(const Color& color) = 0;

	virtual void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) = 0;

	virtual void DrawEllipse(const CPoint& centerPoint, const int widthRadius, const int heightRadius) = 0;

	virtual ~ICanvas() = default;
};