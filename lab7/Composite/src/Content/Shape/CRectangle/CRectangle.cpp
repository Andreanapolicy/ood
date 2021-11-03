#include "CRectangle.h"

CRectangle::CRectangle(PointD point, double width, double height)
	: m_frame({point, width, height})
{
}

void CRectangle::Draw() const
{
	CShape::Draw();
}

FrameD CRectangle::GetFrame() const
{
	return m_frame;
}

void CRectangle::SetFrame(FrameD& frame)
{
	m_frame = frame;
}
