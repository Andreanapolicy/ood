#pragma once
#include "../../FlyBehavior/CFlyWithWings/CFlyWithWings.h"
#include "../../QuackBehavior/CQuackBehavior/CQuackBehavior.h"
#include "../CDuck/CDuck.h"

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuackBehavior>())
	{
	}

	void Display() const override;
};