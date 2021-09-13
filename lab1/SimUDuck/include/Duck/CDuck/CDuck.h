#pragma once
#include "../../DanceBehavior/IDanceBehavior/IDanceBehavior.h"
#include "../../FlyBehavior/IFlyBehavior/IFlyBehavior.h"
#include "../../QuackBehavior/IQuackBehavior/IQuackBehavior.h"
#include <iostream>
#include <memory>

class CDuck
{
public:
	CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior, std::unique_ptr<IQuackBehavior>&& quackBehavior, std::unique_ptr<IDanceBehavior>&& danceBehavior);

	void Quack() const;

	void Swim();

	void Fly();

	void Dance();

	void ShowCountOfFly();

	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior);

	void SetDanceBehavior(std::unique_ptr<IDanceBehavior>&& danceBehavior);

	virtual void Display() const = 0;

	virtual ~CDuck() = default;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior = {};
	std::unique_ptr<IQuackBehavior> m_quackBehavior = {};
	std::unique_ptr<IDanceBehavior> m_danceBehavior = {};
};