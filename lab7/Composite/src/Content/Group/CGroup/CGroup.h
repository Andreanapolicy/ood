#pragma once
#include "../../Style/CBorderStyle/CBorderStyle.h"
#include "../../Style/CBorderGroupStyle/CBorderGroupStyle.h"
#include "../../Style/CFillGroupStyle/CFillGroupStyle.h"
#include "../../Style/IBorderStyle/IBorderStyle.h"
#include "../IGroup/IGroup.h"
#include "../../../Exception/CWrongShapeIndexException/CWrongShapeIndexException.h"
#include "../../../Exception/CEmptyShapeException/CEmptyShapeException.h"
#include "../../../Exception/CStyleNotExistException/CStyleNotExistException.h"

class CGroup : public IGroup, std::enable_shared_from_this<IGroup>
{
public:
	CGroup();

	size_t GetShapesCount() const override;
	std::shared_ptr<IShape> GetShapeAtIndex(const size_t index) override;
	void InsertShape(std::shared_ptr<IShape>& shape, const size_t index) override;
	void RemoveShapeAtIndex(const size_t index) override;

	FrameD GetFrame() const override;
	void SetFrame(FrameD& frame) override;

	std::shared_ptr<IBorderStyle> GetLineStyle() override;
	std::shared_ptr<const IBorderStyle> GetLineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<const IGroup> GetGroup() const override;
	std::shared_ptr<IGroup> GetGroup() override;

	void Draw(ICanvas& canvas) const override;

private:

	bool IsFrameEmpty(FrameD& frame);
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<IBorderStyle> m_borderStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};
