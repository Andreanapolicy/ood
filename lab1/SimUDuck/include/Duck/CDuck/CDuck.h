#pragma once
#include "../../FlyBehavior/IFlyBehavior/IFlyBehavior.h"
#include "../../QuackBehavior/IQuackBehavior/IQuackBehavior.h"
#include <iostream>
#include <memory>

class CDuck
{
public:
	CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior, std::unique_ptr<IQuackBehavior>&& quackBehavior);

	void Quack() const;

	void Swim();

	void Fly();

	virtual void Dance();

	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior);

	virtual void Display() const = 0;

	virtual ~CDuck() = default;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior = {};
	std::unique_ptr<IQuackBehavior> m_quackBehavior = {};
};