#pragma once
#include "../IStyle/IStyle.h"

class IBorderStyle : public IStyle
{
public:
	virtual void SetThickness(double thickness) = 0;

	virtual double GetThickness() const = 0;
};

typedef std::function<void(IBorderStyle& style)> BorderStyleEnumerator;