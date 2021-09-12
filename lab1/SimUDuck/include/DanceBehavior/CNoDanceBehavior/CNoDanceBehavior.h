#pragma once
#include <iostream>
#include "../IDanceBehavior/IDanceBehavior.h"

class CNoDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override;
};