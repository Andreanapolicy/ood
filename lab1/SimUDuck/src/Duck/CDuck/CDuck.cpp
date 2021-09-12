#include "../../../include/Duck/CDuck/CDuck.h"

CDuck::CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior, std::unique_ptr<IQuackBehavior>&& quackBehavior)
	: m_quackBehavior(std::move(quackBehavior))
{
	SetFlyBehavior(move(flyBehavior));
}

void CDuck::Quack() const
{
	m_quackBehavior->Quack();
}

void CDuck::Swim()
{
	std::cout << "I'm swimming" << std::endl;
}

void CDuck::Fly()
{
	m_flyBehavior->Fly();
}

void CDuck::Dance()
{
	std::cout << "I'm Dancing" << std::endl;
}

void CDuck::SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
{
	m_flyBehavior = move(flyBehavior);
}