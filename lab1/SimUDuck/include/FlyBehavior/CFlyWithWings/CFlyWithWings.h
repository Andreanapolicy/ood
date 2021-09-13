#pragma once
#include <iostream>
#include "../IFlyBehavior/IFlyBehavior.h"

class CFlyWithWings : public IFlyBehavior
{
public:
	void Fly() override;

	void ShowCountOfFly() override;

private:
	int m_countOfFly = 0;
};