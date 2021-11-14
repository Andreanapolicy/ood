#pragma once
#include "../../GumballMachine/IGumballMachine/IGumballMachine.h"
#include "../IState/IState.h"
#include "iostream"

class CSoldOutState : public IState
{
public:
	explicit CSoldOutState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
	}

	void EjectQuarter() override
	{
        std::cout << m_gumballMachine.GetQuartersCount() << " quarter ejected successfully" << std::endl;

        m_gumballMachine.ReleaseQuarter(m_gumballMachine.GetQuartersCount());
    }

	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs" << std::endl;
	}

	void Dispense() override
	{
		std::cout << "No gumball dispensed" << std::endl;
	}

	std::string ToString() const override
	{
		return "sold out";
	}

private:
	IGumballMachine& m_gumballMachine;
};