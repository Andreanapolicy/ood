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
		std::cout << "You can't insert another one quarter" << std::endl;
	}

	void EjectQuarter() override
	{
		std::cout << "Quarter ejected successfully" << std::endl;
		m_gumballMachine.SetNoQuarterState();
	}

	void TurnCrank() override
	{
		std::cout << "You turned the crank" << std::endl;
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