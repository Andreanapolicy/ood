#pragma once
#include "../Shape/CShape.h"
#include "./Exception/ShapesIndexOutOfRange.h"
#include <memory>
#include <vector>

class CPictureDraft
{
public:
	size_t GetShapesCount() const
	{
		return m_shapes.size();
	}

	CShape& GetShape(const size_t index) const
	{
		if (index >= GetShapesCount())
		{
			throw ShapesIndexOutOfRange("Error, shapes index out of range");
		}

		return *m_shapes[index];
	}

	void AddShape(std::unique_ptr<CShape>&& shape)
	{
		m_shapes.push_back(std::move(shape));
	}

private:
	std::vector<std::unique_ptr<CShape>> m_shapes{};
};