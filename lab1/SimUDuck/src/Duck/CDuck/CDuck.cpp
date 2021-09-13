#include "../../../include/Duck/CDuck/CDuck.h"

CDuck::CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior, std::unique_ptr<IQuackBehavior>&& quackBehavior, std::unique_ptr<IDanceBehavior>&& danceBehavior)
	: m_quackBehavior(std::move(quackBehavior))
{
	SetFlyBehavior(move(flyBehavior));
	SetDanceBehavior(move(danceBehavior));
}

void CDuck::Quack() const
{
	m_quackBehavior->Quack();
}

void CDuck::Swim() const
{
	std::cout << "I'm swimming" << std::endl;
}

void CDuck::Fly() const
{
	m_flyBehavior->Fly();
}

void CDuck::Dance() const
{
	m_danceBehavior->Dance();
}

void CDuck::ShowCountOfFly() const
{
	m_flyBehavior->ShowCountOfFly();
}

void CDuck::SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
{
	m_flyBehavior = move(flyBehavior);
}

void CDuck::SetDanceBehavior(std::unique_ptr<IDanceBehavior>&& danceBehavior)
{
	m_danceBehavior = move(danceBehavior);
}