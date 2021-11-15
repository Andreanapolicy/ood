#pragma once
#include "../../GumballMachine/IGumballMachine/IGumballMachine.h"
#include "../IState/IState.h"
#include "iostream"

class CHasQuarterState : public IState
{
public:
	explicit CHasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter" << std::endl;
        m_gumballMachine.AddQuarter();

        if (m_gumballMachine.GetQuartersCount() == maxQuarterCount)
        {
            m_gumballMachine.SetMaxQuarterCountState();
        }
	}

    void InsertBalls(unsigned int count) override
    {
        std::cout << "You inserted a balls" << std::endl;

        m_gumballMachine.AddBalls(count);
    }

	void EjectQuarter() override
	{
		std::cout << m_gumballMachine.GetQuartersCount() << " quarter ejected successfully" << std::endl;

        m_gumballMachine.ReleaseQuarter(m_gumballMachine.GetQuartersCount());
		m_gumballMachine.SetNoQuarterState();
	}

	void TurnCrank() override
	{
		std::cout << "You turned the crank" << std::endl;

        m_gumballMachine.ReleaseQuarter(1);
        m_gumballMachine.SetSoldState();
	}

	void Dispense() override
	{
		std::cout << "You need to insert a quarter first" << std::endl;
	}

	std::string ToString() const override
	{
		return "waiting for turning the crank";
	}

private:
	IGumballMachine& m_gumballMachine;
};