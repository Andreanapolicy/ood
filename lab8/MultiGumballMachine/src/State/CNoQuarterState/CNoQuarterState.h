#pragma once
#include "../../GumballMachine/IGumballMachine/IGumballMachine.h"
#include "../IState/IState.h"
#include "iostream"

class CNoQuarterState : public IState
{
public:
	explicit CNoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter" << std::endl;

        m_gumballMachine.AddQuarter();
		m_gumballMachine.SetHasQuarterState();
	}

	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter for ejection" << std::endl;
	}

	void TurnCrank() override
	{
		std::cout << "You need to insert a quarter first but not turning" << std::endl;
	}

	void Dispense() override
	{
		std::cout << "You need to insert a quarter first" << std::endl;
	}

	std::string ToString() const override
	{
		return "waiting for quarter";
	}

private:
	IGumballMachine& m_gumballMachine;
};