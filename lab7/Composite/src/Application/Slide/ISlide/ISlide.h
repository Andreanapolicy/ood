#pragma once
#include "../../../Content/Shape/IDrawable/IDrawable.h"
#include "../../../Content/Shape/IShape/IShape.h"

class ISlide : public IDrawable
{
public:
	virtual size_t GetShapesCount() const = 0;

	virtual std::shared_ptr<IShape> GetShapeAtIndex(const size_t index) = 0;

	virtual void InsertShape(std::shared_ptr<IShape> shape, const size_t index) = 0;

	virtual void RemoveShapeAtIndex(const size_t index) = 0;

	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;
};