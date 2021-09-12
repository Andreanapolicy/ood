#pragma once
#include <iostream>
#include "../IQuackBehavior/IQuackBehavior.h"

class CQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override;
};