#pragma once
#include "../Canvas/ICanvas.h"
#include "../Point/CPoint.h"
#include "./CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(const Color& color, const CPoint& centerPoint, const int widthRadius, const int heightRadius)
		: CShape(color)
		, m_centerPoint(centerPoint)
		, m_widthRadius(widthRadius)
		, m_heightRadius(heightRadius)
	{
	}

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(GetColor());
		canvas.DrawEllipse(m_centerPoint, m_widthRadius, m_heightRadius);
	}

	const CPoint& GetCenterPoint() const
	{
		return m_centerPoint;
	}

	int GetWidthRadius() const
	{
		return m_widthRadius;
	}

	int GetHeightRadius() const
	{
		return m_heightRadius;
	}

private:
	CPoint m_centerPoint;
	int m_widthRadius;
	int m_heightRadius;
};