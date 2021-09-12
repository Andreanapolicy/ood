#pragma once
#include <iostream>
#include "../IDanceBehavior/IDanceBehavior.h"

class CWaltzBehavior : public IDanceBehavior
{
public:
	void Dance() override;
};