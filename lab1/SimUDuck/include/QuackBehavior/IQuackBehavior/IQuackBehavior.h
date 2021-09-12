#pragma once

class IQuackBehavior
{
public:
	virtual ~IQuackBehavior() = default;
	virtual void Quack() = 0;
};