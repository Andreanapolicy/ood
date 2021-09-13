#pragma once
#include "../IFlyBehavior/IFlyBehavior.h"

class CFlyNoWay : public IFlyBehavior
{
public:
	void Fly() override;

	void ShowCountOfFly() override;
};