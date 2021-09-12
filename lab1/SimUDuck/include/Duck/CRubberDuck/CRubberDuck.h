#pragma once
#include "../../DanceBehavior/CNoDanceBehavior/CNoDanceBehavior.h"
#include "../../FlyBehavior/CFlyWithWings/CFlyWithWings.h"
#include "../../QuackBehavior/CQuackBehavior/CQuackBehavior.h"
#include "../CDuck/CDuck.h"

class CRubberDuck : public CDuck
{
public:
	CRubberDuck()
		: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuackBehavior>(), std::make_unique<CNoDanceBehavior>())
	{
	}

	void Display() const override;
};