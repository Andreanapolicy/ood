#pragma once
#include "../../GumballMachine/IGumballMachine/IGumballMachine.h"
#include "../IState/IState.h"
#include "iostream"

class CMaxQuarterCountState : public IState
{
public:
    explicit CMaxQuarterCountState(IGumballMachine& gumballMachine)
            : m_gumballMachine(gumballMachine)
    {
    }

    void InsertQuarter() override
    {
        std::cout << "You can't insert another one quarter. Max value was reached(" << maxQuarterCount << ")" << std::endl;
    }

    void InsertBalls(unsigned int count) override
    {
        std::cout << "You inserted a balls" << std::endl;

        m_gumballMachine.AddBalls(count);
    }

    void EjectQuarter() override
    {
        std::cout << maxQuarterCount << " quarter ejected successfully" << std::endl;

        m_gumballMachine.ReleaseQuarter(maxQuarterCount);
        m_gumballMachine.SetNoQuarterState();
    }

    void TurnCrank() override
    {
        std::cout << "You turned the crank" << std::endl;

        m_gumballMachine.ReleaseQuarter();
        m_gumballMachine.SetSoldState();
    }

    void Dispense() override
    {
        std::cout << "You need to turn thr crack" << std::endl;
    }

    std::string ToString() const override
    {
        return "Quarters count is full. Waiting for turning the crank";
    }

private:
    IGumballMachine& m_gumballMachine;
};