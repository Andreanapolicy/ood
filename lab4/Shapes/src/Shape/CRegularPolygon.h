#pragma once
#include "../Canvas/ICanvas.h"
#include "../Point/CPoint.h"
#include "./CShape.h"
#include "./Exception/InvalidVertexCountException.h"
#include <vector>
#include <cmath>

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(const Color& color, const int vertexCount, const CPoint& centerPoint, const int radius)
		: CShape(color)
		, m_centerPoint(centerPoint)
		, m_radius(radius)
	{
		if (vertexCount <= 2)
		{
			throw InvalidVertexCountException("Error, count of vertex must be greater then 2");
		}

		m_vertexCount = vertexCount;
	}

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(GetColor());

		std::vector<CPoint> vertexes = GetVertexes();

		for (auto index = 0; index < m_vertexCount - 1; index++)
		{
			canvas.DrawLine(vertexes[index], vertexes[index + 1]);
		}

		canvas.DrawLine( vertexes[m_vertexCount - 1], vertexes[0]);
	}

	std::vector<CPoint> GetVertexes() const
	{
		std::vector<CPoint> vertexes;
		auto angle = 2 * M_PI / m_vertexCount;

		for (auto index = 0; index < m_vertexCount; index++)
		{
			vertexes.push_back({
				m_centerPoint.getX() + m_radius * cos(angle * index),
				m_centerPoint.getY() + m_radius * sin(angle * index)
			});
		}

		return vertexes;
	}

	int GetVertexCount() const
	{
		return m_vertexCount;
	}

	const CPoint& GetCenterPoint() const
	{
		return m_centerPoint;
	}

	int GetRadius() const
	{
		return m_radius;
	}

private:
	int m_vertexCount;
	CPoint m_centerPoint;
	int m_radius;
};