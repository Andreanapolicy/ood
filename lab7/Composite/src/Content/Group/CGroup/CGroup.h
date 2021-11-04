#pragma once
#include "../../Style/CBorderStyle/CBorderStyle.h"
#include "../../Style/CFillStyle/CFillStyle.h"
#include "../../Style/IBorderStyle/IBorderStyle.h"
#include "../IGroup/IGroup.h"

class CGroup : IGroup
{
public:
	CGroup();

	int GetShapesCount() const override;
	std::shared_ptr<IShape> GetShapeAtIndex(const size_t index) override;
	void InsertShape(std::shared_ptr<IShape>& shape, const size_t index) override;
	void RemoveShapeAtIndex(const size_t index) override;

	FrameD GetFrame() const override;
	void SetFrame(FrameD& frame) override;

	std::shared_ptr<IBorderStyle> GetLineStyle() override;
	std::shared_ptr<const IBorderStyle> GetLineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<IGroup> GetGroup() const override;

	void Draw(ICanvas& canvas) const override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<IBorderStyle> m_borderStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};
