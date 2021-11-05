#pragma once
#include "../../../Content/Shape/IDrawable/IDrawable.h"
#include "../../../Content/Composite/IComposite/IComposite.h"

class ISlide : public IDrawable, public IComposite
{
public:
	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;
};