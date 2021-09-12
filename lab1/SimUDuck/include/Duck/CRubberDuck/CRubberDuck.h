#pragma once
#include "../../FlyBehavior/CFlyWithWings/CFlyWithWings.h"
#include "../../QuackBehavior/CQuackBehavior/CQuackBehavior.h"
#include "../CDuck/CDuck.h"

class CRubberDuck : public CDuck
{
public:
	CRubberDuck()
		: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuackBehavior>())
	{
	}

	void Display() const override;
};