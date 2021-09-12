#pragma once
#include <iostream>
#include "../IFlyBehavior/IFlyBehavior.h"

class CFlyWithWings : public IFlyBehavior
{
public:
	void Fly() override;
};