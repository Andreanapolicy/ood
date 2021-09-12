#pragma once
#include "../../FlyBehavior/CFlyWithWings/CFlyWithWings.h"
#include "../../QuackBehavior/CQuackBehavior/CQuackBehavior.h"
#include "../CDuck/CDuck.h"

class CDecoyDuck : public CDuck
{
public:
	CDecoyDuck()
		: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuackBehavior>())
	{
	}

	void Display() const override;

	void Dance() override {}
};