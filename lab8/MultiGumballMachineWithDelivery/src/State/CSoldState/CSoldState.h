#pragma once
#include "../IState/IState.h"
#include "../../GumballMachine/IGumballMachine/IGumballMachine.h"
#include "iostream"

class CSoldState : public IState
{
public:
	explicit CSoldState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
        m_gumballMachine.AddQuarter();
		std::cout << "You insert a quarter. Please wait, we're already giving you a gumball" << std::endl;
	}

	void InsertBalls(unsigned int count) override
	{
		std::cout << "Please wait until your gumball is dispensed" << std::endl;
	}

	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank" << std::endl;
	}

	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball" << std::endl;
	}

	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();

		if (m_gumballMachine.GetBallsCount() == 0)
		{
			std::cout << "Oops, out of gumballs" << std::endl;
			m_gumballMachine.SetSoldOutState();

			return;
		}

        if (m_gumballMachine.GetQuartersCount() > 0)
        {
            m_gumballMachine.SetHasQuarterState();

            return;
        }

		m_gumballMachine.SetNoQuarterState();
	}

	std::string ToString() const override
	{
		return "delivering a gumball";
	}

private:
	IGumballMachine& m_gumballMachine;
};