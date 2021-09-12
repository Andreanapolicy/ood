#pragma once
#include "../IQuackBehavior/IQuackBehavior.h"

class CMuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override;
};