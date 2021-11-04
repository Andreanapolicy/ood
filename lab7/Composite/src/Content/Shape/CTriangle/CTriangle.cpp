#include "CTriangle.h"

CTriangle::CTriangle(PointD firstVertex, PointD secondVertex, PointD thirdVertex)
	: m_firstVertex(firstVertex)
	, m_secondVertex(secondVertex)
	, m_thirdVertex(thirdVertex)
{
}

void CTriangle::Draw(ICanvas& canvas) const
{
	if (GetLineStyle()->isEnable())
	{
		canvas.DrawLine(m_firstVertex, m_secondVertex, GetLineStyle()->GetColor(), GetLineStyle()->GetThickness());
		canvas.DrawLine(m_secondVertex, m_thirdVertex, GetLineStyle()->GetColor(), GetLineStyle()->GetThickness());
		canvas.DrawLine(m_thirdVertex, m_firstVertex, GetLineStyle()->GetColor(), GetLineStyle()->GetThickness());
	}

	std::vector<PointD> points = {m_firstVertex, m_secondVertex, m_thirdVertex};

	if (GetFillStyle()->isEnable())
	{
		canvas.FillPolygon(points, GetFillStyle()->GetColor());
	}
}

FrameD CTriangle::GetFrame() const
{
	auto maxX = std::max({ m_firstVertex.x, m_secondVertex.x, m_thirdVertex.x });
	auto minX = std::min({ m_firstVertex.x, m_secondVertex.x, m_thirdVertex.x });
	auto maxY = std::max({ m_firstVertex.y, m_secondVertex.y, m_thirdVertex.y });
	auto minY = std::min({ m_firstVertex.y, m_secondVertex.y, m_thirdVertex.y });

	return FrameD{{minX, minY}, maxX - minX, maxY - minY};
}

void CTriangle::SetFrame(FrameD& frame)
{
	std::vector<PointD*> points = {&m_firstVertex, &m_secondVertex, &m_thirdVertex};

	auto currentFrame = GetFrame();
	auto m_coefX = frame.width / currentFrame.width;
	auto m_coefY = frame.height / currentFrame.height;

	for (auto& point : points)
	{
		*point = {
			frame.leftTopPoint.x + (point->x - currentFrame.leftTopPoint.x) * m_coefX,
			frame.leftTopPoint.y + (point->y - currentFrame.leftTopPoint.y) * m_coefY
		};
	}
}
