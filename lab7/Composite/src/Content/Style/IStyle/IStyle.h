#pragma once
#include "../../../Common/Color/Color.h"

class IStyle
{
public:
	virtual bool isEnable() const = 0;

	virtual void Enable() = 0;

	virtual void Disable() = 0;

	virtual Color GetColor() const = 0;

	virtual void SetColor(Color color) = 0;

	virtual ~IStyle() = default;

};