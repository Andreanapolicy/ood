#pragma once
#include "../Canvas/ICanvas.h"
#include "../Point/CPoint.h"
#include "./CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const Color& color, const CPoint& topLeftPoint, const int width, const int height)
		: CShape(color)
		, m_topLeftPoint(topLeftPoint)
		, m_width(width)
		, m_height(height)
	{
	}

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(GetColor());
		CPoint topRightPoint(m_topLeftPoint.getX() + m_width, m_topLeftPoint.getY());
		CPoint bottomRightPoint(m_topLeftPoint.getX() + m_width, m_topLeftPoint.getY() - m_height);
		CPoint bottomLeftPoint(m_topLeftPoint.getX(), m_topLeftPoint.getY() - m_height);

		canvas.DrawLine(m_topLeftPoint, topRightPoint);
		canvas.DrawLine(topRightPoint, bottomRightPoint);
		canvas.DrawLine(bottomRightPoint, bottomLeftPoint);
		canvas.DrawLine(bottomLeftPoint, m_topLeftPoint);
	}

	const CPoint& GetTopLeftPoint() const
	{
		return m_topLeftPoint;
	}

	int GetWidth() const
	{
		return m_width;
	}

	int GetHeight() const
	{
		return m_height;
	}

private:
	CPoint m_topLeftPoint;
	int m_width;
	int m_height;
};