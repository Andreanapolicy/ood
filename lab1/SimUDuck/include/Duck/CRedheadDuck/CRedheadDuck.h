#pragma once
#include "../../FlyBehavior/CFlyWithWings/CFlyWithWings.h"
#include "../../QuackBehavior/CQuackBehavior/CQuackBehavior.h"
#include "../CDuck/CDuck.h"

class CRedheadDuck : public CDuck
{
public:
	CRedheadDuck()
		: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuackBehavior>())
	{
	}

	void Display() const override;
};