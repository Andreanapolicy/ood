#pragma once
#include "../ISlide/ISlide.h"
#include "../../../Exception/CWrongShapeIndexException/CWrongShapeIndexException.h"
#include "../../../Exception/CEmptyShapeException/CEmptyShapeException.h"

class CSlide : public ISlide
{
public:
	CSlide(double width, double height);

	size_t GetShapesCount() const override;

	std::shared_ptr<IShape> GetShapeAtIndex(const size_t index) override;

	void InsertShape(std::shared_ptr<IShape> shape, const size_t index) override;

	void RemoveShapeAtIndex(const size_t index) override;

	void Draw(ICanvas& canvas) const override;

	double GetWidth() const override;

	double GetHeight() const override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;

	double m_width;
	double m_height;
};
