#include "CRectangle.h"

CRectangle::CRectangle(PointD point, double width, double height)
	: m_frame({point, width, height})
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	std::vector<PointD> points = {
		m_frame.leftTopPoint,
		{ m_frame.leftTopPoint.x + m_frame.width, m_frame.leftTopPoint.y },
		{ m_frame.leftTopPoint.x + m_frame.width, m_frame.leftTopPoint.y + m_frame.height },
		{ m_frame.leftTopPoint.x, m_frame.leftTopPoint.y + m_frame.height },
	};

	if (GetLineStyle()->isEnable())
	{
		canvas.DrawLine(points[0], points[1], GetLineStyle()->GetColor(), GetLineStyle()->GetThickness());
		canvas.DrawLine(points[1], points[2], GetLineStyle()->GetColor(), GetLineStyle()->GetThickness());
		canvas.DrawLine(points[2], points[3], GetLineStyle()->GetColor(), GetLineStyle()->GetThickness());
		canvas.DrawLine(points[3], points[0], GetLineStyle()->GetColor(), GetLineStyle()->GetThickness());
	}

	if (GetFillStyle()->isEnable())
	{
		canvas.FillPolygon(points, GetFillStyle()->GetColor());
	}
}

FrameD CRectangle::GetFrame() const
{
	return m_frame;
}

void CRectangle::SetFrame(FrameD& frame)
{
	m_frame = frame;
}
