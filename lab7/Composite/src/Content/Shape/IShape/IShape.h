#pragma once
#include "../../Style/IStyle/IStyle.h"
#include "../IDrawable/IDrawable.h"
#include "../../../Common/Frame/Frame.h"
#include <memory>

class IGroup;

class IShape : public IDrawable
{
public:
	virtual FrameD GetFrame() const = 0;

	virtual void SetFrame(FrameD& frame) = 0;

	virtual std::shared_ptr<IStyle> GetLineStyle() = 0;

	virtual std::shared_ptr<const IStyle> GetLineStyle() const = 0;

	virtual std::shared_ptr<IStyle> GetFillStyle() = 0;

	virtual std::shared_ptr<const IStyle> GetFillStyle() const = 0;

	virtual std::shared_ptr<IGroup> GetGroup() const = 0;

	~IShape() = default;
};