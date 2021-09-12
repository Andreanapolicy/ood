#pragma once
#include <iostream>
#include "../IDanceBehavior/IDanceBehavior.h"

class CMinuetBehavior : public IDanceBehavior
{
public:
	void Dance() override;
};