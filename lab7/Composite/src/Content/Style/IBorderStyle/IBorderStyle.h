#pragma once
#include "../IStyle/IStyle.h"

class IBorderStyle : public IStyle
{
public:
	virtual void SetThickness(double thickness) = 0;

	virtual std::optional<double> GetThickness() const = 0;
};