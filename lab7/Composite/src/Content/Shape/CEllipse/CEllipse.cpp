#include "CEllipse.h"

CEllipse::CEllipse(PointD center, double widthRadius, double heightRadius)
	: m_center(center)
	, m_widthRadius(widthRadius)
	, m_heightRadius(heightRadius)
{
}

void CEllipse::Draw(ICanvas& canvas) const
{
	if (GetLineStyle()->isEnable())
	{
		canvas.DrawEllipse(
			m_center,
			m_widthRadius,
			m_heightRadius,
			GetLineStyle()->GetColor().value(),
			GetLineStyle()->GetThickness().value());
	}

	if (GetFillStyle()->isEnable())
	{
		canvas.FillEllipse(
			m_center,
			m_widthRadius,
			m_heightRadius,
			GetFillStyle()->GetColor().value());
	}
}

std::optional<FrameD> CEllipse::GetFrame() const
{
	return FrameD(
		{ m_center.x - m_widthRadius, m_center.y - m_heightRadius,
			m_widthRadius * 2,
			m_heightRadius * 2 });
}

void CEllipse::SetFrame(FrameD& frame)
{
	m_center = { frame.leftTopPoint.x + frame.width / 2, frame.leftTopPoint.y + frame.height / 2 };
	m_widthRadius = frame.width / 2;
	m_heightRadius = frame.height / 2;
}