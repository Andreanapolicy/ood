#include "CGroup.h"

CGroup::CGroup()
	: m_borderStyle(std::make_shared<CBorderStyle>())
	, m_fillStyle(std::make_shared<CFillStyle>())
{
}

int CGroup::GetShapesCount() const
{
	return 0;
}

std::shared_ptr<IShape> CGroup::GetShapeAtIndex(const size_t index)
{
	return std::shared_ptr<IShape>();
}

void CGroup::InsertShape(std::shared_ptr<IShape>& shape, const size_t index)
{
}

void CGroup::RemoveShapeAtIndex(const size_t index)
{
}

void CGroup::Draw(ICanvas& canvas) const
{
}

FrameD CGroup::GetFrame() const
{
	return FrameD();
}

void CGroup::SetFrame(FrameD& frame)
{
}

std::shared_ptr<IBorderStyle> CGroup::GetLineStyle()
{
	return nullptr;
}

std::shared_ptr<const IBorderStyle> CGroup::GetLineStyle() const
{
	return nullptr;
}

std::shared_ptr<IStyle> CGroup::GetFillStyle()
{
	return std::shared_ptr<IStyle>();
}

std::shared_ptr<const IStyle> CGroup::GetFillStyle() const
{
	return std::shared_ptr<const IStyle>();
}

std::shared_ptr<IGroup> CGroup::GetGroup() const
{
	return std::shared_ptr<IGroup>();
}
