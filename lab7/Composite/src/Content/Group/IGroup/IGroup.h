#pragma once
#include "../../Shape/IShape/IShape.h"

class IGroup : public IShape
{
	virtual size_t GetShapesCount() const = 0;

	virtual std::shared_ptr<IShape> GetShapeAtIndex(const size_t index) = 0;

	virtual void InsertShape(std::shared_ptr<IShape> shape, const size_t index) = 0;

	virtual void RemoveShapeAtIndex(const size_t index) = 0;
};