#pragma once
#include "../../Style/IBorderStyle/IBorderStyle.h"
#include "../../Style/CFillStyle/CFillStyle.h"
#include "../../Style/CBorderStyle/CBorderStyle.h"
#include "../IShape/IShape.h"

class CShape : public IShape
{
public:
	CShape();

	std::shared_ptr<IStyle> GetLineStyle() override;

	std::shared_ptr<const IStyle> GetLineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;

	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<IGroup> GetGroup() const override;

protected:
	void Draw() const = 0;

	virtual FrameD GetFrame() const = 0;

	virtual void SetFrame(FrameD& frame) = 0;

private:
	std::shared_ptr<IBorderStyle> m_borderStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};
