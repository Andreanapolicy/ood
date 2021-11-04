#pragma once
#include "../../../Application/Canvas/ICanvas/ICanvas.h"

class IDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;

	~IDrawable() = default;
};