#pragma once
#include "../../DanceBehavior/CWaltzBehavior/CWaltzBehavior.h"
#include "../../FlyBehavior/CFlyWithWings/CFlyWithWings.h"
#include "../../QuackBehavior/CQuackBehavior/CQuackBehavior.h"
#include "../CDuck/CDuck.h"

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuackBehavior>(), std::make_unique<CWaltzBehavior>())
	{
	}

	void Display() const override;
};