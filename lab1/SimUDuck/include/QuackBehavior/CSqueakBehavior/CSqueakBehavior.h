#pragma once
#include <iostream>
#include "../IQuackBehavior/IQuackBehavior.h"

class CSqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override;
};
