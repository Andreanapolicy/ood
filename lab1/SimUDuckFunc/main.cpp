#include <iostream>
#include <functional>

#include "include/FlyBehavior/FlyWithWings/FlyWithWings.h"
#include "include/QuackBehavior/QuackBehavior/QuackBehavior.h"
#include "include/DanceBehavior/WaltzBehavior/WaltzBehavior.h"
#include "include/DanceBehavior/NoDanceBehavior/NoDanceBehavior.h"
#include "include/QuackBehavior/SqueakBehavior/SqueakBehavior.h"
#include "include/DanceBehavior/MinuetBehavior/MinuetBehavior.h"

class CDuck
{
public:
    CDuck(std::function<void()>&& flyBehavior, std::function<void()>&& quackBehavior, std::function<void()>&& danceBehavior)
            : m_quackBehavior(std::move(quackBehavior))
    {
        SetFlyBehavior(move(flyBehavior));
        SetDanceBehavior(move(danceBehavior));
    }

    void Quack() const
    {
        m_quackBehavior();
    }

    void Swim() const
    {
        std::cout << "I'm swimming" << std::endl;
    }

    void Fly() const
    {
        m_flyBehavior();
    }

    void Dance() const
    {
        m_danceBehavior();
    }

    void SetFlyBehavior(std::function<void()>&& flyBehavior)
    {
        m_flyBehavior = std::move(flyBehavior);
    }

    void SetDanceBehavior(std::function<void()>&& danceBehavior)
    {
        m_danceBehavior = std::move(danceBehavior);
    }

    virtual void Display() const = 0;

    virtual ~CDuck() = default;

private:
    std::function<void()> m_flyBehavior;
    std::function<void()> m_quackBehavior;
    std::function<void()> m_danceBehavior;
};

class CDecoyDuck : public CDuck
{
public:
    CDecoyDuck()
            : CDuck(flyWithWings, quack, noDance)
    {
    }

    void Display() const override
    {
        std::cout << "I'm decoy duck" << std::endl;
    }
};

class CMallardDuck : public CDuck
{
public:
    CMallardDuck()
            : CDuck(flyWithWings, quack, danceWaltz)
    {
    }

    void Display() const override
    {
        std::cout << "I'm mallard duck" << std::endl;
    }
};

class CRedheadDuck : public CDuck
{
public:
    CRedheadDuck()
            : CDuck(flyWithWings, squeak, danceMinuet)
    {
    }

    void Display() const override
    {
        std::cout << "I'm redhead duck" << std::endl;
    }
};

class CRubberDuck : public CDuck
{
public:
    CRubberDuck()
            : CDuck(flyWithWings, quack, noDance)
    {
    }

    void Display() const override
    {
        std::cout << "I'm rubber duck" << std::endl;
    }
};

void PlayWithDuck(CDuck& duck)
{
    duck.Display();
    duck.Quack();
    duck.Swim();
    duck.Fly();
    duck.Fly();
    duck.Dance();

    std::cout << std::endl;
}

int main()
{
    CMallardDuck mallardDuck;
    PlayWithDuck(mallardDuck);

    CRedheadDuck redheadDuck;
    PlayWithDuck(redheadDuck);

    CRubberDuck rubberDuck;
    PlayWithDuck(rubberDuck);

    CDecoyDuck decoyDuck;
    PlayWithDuck(decoyDuck);

    decoyDuck.SetFlyBehavior(flyWithWings);
    PlayWithDuck(decoyDuck);
}