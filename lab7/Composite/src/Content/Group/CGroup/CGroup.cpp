#include "CGroup.h"

CGroup::CGroup()
{
	BorderGroupEnumerator borderGroupEnumerator = [this](BorderStyleEnumerator styleEnumerator) {
		for (const auto& shape : m_shapes)
		{
			styleEnumerator(*shape->GetLineStyle());
		}
	};

	m_borderStyle = std::make_shared<CBorderGroupStyle>(borderGroupEnumerator);

	FillGroupEnumerator fillGroupEnumerator = [this](StyleCallback StyleCallback) {
		for (const auto& shape : m_shapes)
		{
			StyleCallback(*shape->GetFillStyle());
		}
	};

	m_fillStyle = std::make_shared<CFillGroupStyle>(fillGroupEnumerator);
}

size_t CGroup::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> CGroup::GetShapeAtIndex(const size_t index)
{
	if (index >= GetShapesCount())
	{
		throw CWrongShapeIndexException("Error, wrong index of shape");
	}

	return m_shapes.at(index);
}

void CGroup::InsertShape(std::shared_ptr<IShape> shape, const size_t index)
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

void CGroup::RemoveShapeAtIndex(const size_t index)
{
	if (index >= GetShapesCount())
	{
		throw CWrongShapeIndexException("Error, wrong index of shape");
	}

	m_shapes.erase(m_shapes.begin() + index);
}

void CGroup::Draw(ICanvas& canvas) const
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

std::optional<FrameD> CGroup::GetFrame() const
{
	if (m_shapes.empty())
	{
		return std::nullopt;
	}

	double maxX = std::numeric_limits<double>::min();
	double minX = std::numeric_limits<double>::max();
	double maxY = std::numeric_limits<double>::min();
	double minY = std::numeric_limits<double>::max();

	for (const auto& shape : m_shapes)
	{
		auto frame = shape->GetFrame().value();

		maxX = std::max(maxX, frame.leftTopPoint.x + frame.width);
		minX = std::min(minX, frame.leftTopPoint.x);
		maxY = std::max(maxY, frame.leftTopPoint.y + frame.height);
		minY = std::min(minY, frame.leftTopPoint.y);
	}

	return FrameD{ { minX, minY }, maxX - minX, maxY - minY };
}

void CGroup::SetFrame(FrameD& frame)
{
	auto currentFrame = GetFrame().value();

	if (IsFrameEmpty(currentFrame))
	{
		return;
	}

	auto coefX = frame.width / currentFrame.width;
	auto coefY = frame.height / currentFrame.height;

	for (const auto& shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame().value();

		auto leftPointX = frame.leftTopPoint.x + (shapeFrame.leftTopPoint.x - currentFrame.leftTopPoint.x) * coefX;
		auto leftPointY = frame.leftTopPoint.y + (shapeFrame.leftTopPoint.y - currentFrame.leftTopPoint.y) * coefY;
		auto width = shapeFrame.width * coefX;
		auto height = shapeFrame.height * coefY;

		FrameD newFrame{ { leftPointX, leftPointY }, width, height };
		shape->SetFrame(newFrame);
	}
}

std::shared_ptr<IBorderStyle> CGroup::GetLineStyle()
{
	if (!m_borderStyle)
	{
		throw CStyleNotExistException("Error, border style not found");
	}

	return m_borderStyle;
}

std::shared_ptr<const IBorderStyle> CGroup::GetLineStyle() const
{
	if (!m_borderStyle)
	{
		throw CStyleNotExistException("Error, border style not found");
	}

	return m_borderStyle;
}

std::shared_ptr<IStyle> CGroup::GetFillStyle()
{
	if (!m_fillStyle)
	{
		throw CStyleNotExistException("Error, fill style not found");
	}

	return m_fillStyle;
}

std::shared_ptr<const IStyle> CGroup::GetFillStyle() const
{
	if (!m_fillStyle)
	{
		throw CStyleNotExistException("Error, fill style not found");
	}

	return m_fillStyle;
}

std::shared_ptr<IGroup> CGroup::GetGroup()
{
	return shared_from_this();
}

std::shared_ptr<const IGroup> CGroup::GetGroup() const
{
	return shared_from_this();
}

bool CGroup::IsFrameEmpty(FrameD& frame)
{
	return frame.width == 0 && frame.height == 0 && frame.leftTopPoint.x == 0 && frame.leftTopPoint.y == 0;
}