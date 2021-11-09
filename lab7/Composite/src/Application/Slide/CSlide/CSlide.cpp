#include "CSlide.h"

CSlide::CSlide(double width, double height)
	: m_width(width)
	, m_height(height)
{
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(const size_t index)
{
	if (index >= GetShapesCount())
	{
		throw CWrongShapeIndexException("Error, wrong index of shape");
	}

	return m_shapes.at(index);
}

void CSlide::InsertShape(std::shared_ptr<IShape> shape, const size_t index)
{
	if (shape == nullptr)
	{
		throw CEmptyShapeException("Error, shape pointer is nullptr");
	}

	if (index > GetShapesCount() || index < 0)
	{
		throw CWrongShapeIndexException("Error, wrong index to insert shape");
	}

	m_shapes.emplace(m_shapes.begin() + index, std::move(shape));
}

void CSlide::RemoveShapeAtIndex(const size_t index)
{
	if (index >= GetShapesCount())
	{
		throw CWrongShapeIndexException("Error, wrong index of shape");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

void CSlide::Draw(ICanvas& canvas) const
{
	for (const auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}
