#pragma once
#include "../Canvas/ICanvas.h"
#include "../Point/CPoint.h"
#include "./CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(const Color& color, const CPoint& firstVertex, const CPoint& secondVertex, const CPoint& thirdVertex)
		: CShape(color)
		, m_firstVertex(firstVertex)
		, m_secondVertex(secondVertex)
		, m_thirdVertex(thirdVertex)
	{
	}

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(GetColor());
		canvas.DrawLine(m_firstVertex, m_secondVertex);
		canvas.DrawLine(m_secondVertex, m_thirdVertex);
		canvas.DrawLine(m_thirdVertex, m_firstVertex);
	}

	const CPoint& GetFirstVertex() const
	{
		return m_firstVertex;
	}

	const CPoint& GetSecondVertex() const
	{
		return m_secondVertex;
	}

	const CPoint& GetThirdVertex() const
	{
		return m_thirdVertex;
	}

private:
	CPoint m_firstVertex;
	CPoint m_secondVertex;
	CPoint m_thirdVertex;
};