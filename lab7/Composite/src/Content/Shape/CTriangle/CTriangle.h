#pragma once
#include "../CShape/CShape.h"
#include <cmath>

class CTriangle : public CShape
{
public:
	CTriangle(PointD firstVertex, PointD secondVertex, PointD thirdVertex);

	void Draw(ICanvas& canvas) const override;

	FrameD GetFrame() const override;

	void SetFrame(FrameD& frame) override;

private:
	PointD m_firstVertex;
	PointD m_secondVertex;
	PointD m_thirdVertex;

};
