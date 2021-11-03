#include "CShape.h"

CShape::CShape()
	: m_borderStyle(std::make_shared<CBorderStyle>())
	, m_fillStyle(std::make_shared<CFillStyle>())
{
}

std::shared_ptr<IStyle> CShape::GetLineStyle()
{
	return m_borderStyle;
}

std::shared_ptr<const IStyle> CShape::GetLineStyle() const
{
	return m_borderStyle;
}

std::shared_ptr<const IStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<IGroup> CShape::GetGroup() const
{
	return nullptr;
}

void CShape::Draw() const
{
}
