#pragma once
#include "../CShape/CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(PointD center, double widthRadius, double heightRadius);

	void Draw(ICanvas& canvas) const override;

	FrameD GetFrame() const override;

	void SetFrame(FrameD& frame) override;

private:
	PointD m_center;
	double m_widthRadius;
	double m_heightRadius;
};
