#pragma once
#include "../CShape/CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(PointD point, double width, double height);

	void Draw(ICanvas& canvas) const override;

	FrameD GetFrame() const override;

	void SetFrame(FrameD& frame) override;

private:
	FrameD m_frame;
};
