#pragma once
#include <iostream>
#include <map>

constexpr int maxQuarterCount = 5;

class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,
		NoQuarter,
		HasQuarter,
		Sold,
		MaxQuarters,
	};

	explicit CGumballMachine(unsigned int count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "You inserted another quarter" << std::endl;
			m_quarterCount++;

			break;
		case State::NoQuarter:
			std::cout << "You inserted a quarter" << std::endl;
			m_state = State::HasQuarter;
			m_quarterCount++;

			break;
		case State::HasQuarter:
			std::cout << "You inserted another quarter" << std::endl;
			m_quarterCount++;
			m_state = m_quarterCount == maxQuarterCount ? State::MaxQuarters : m_state;

			break;
		case State::MaxQuarters:
			std::cout << "You can't insert another quarter: max " << maxQuarterCount << " quarters" << std::endl;

			break;
		case State::Sold:
			std::cout << "You can't insert another one quarter. Max value was reached(" << maxQuarterCount << ")" << std::endl;

			break;
		}
	}

	void EjectQuarter()
	{
		switch (m_state)
		{
		case State::MaxQuarters:
		case State::HasQuarter:
			std::cout << "Quarter returned (" << m_quarterCount << ")" << std::endl;
			m_quarterCount = 0;
			m_state = State::NoQuarter;

			break;
		case State::NoQuarter:
			std::cout << "You haven't inserted a quarter" << std::endl;

			break;
		case State::Sold:
			std::cout << "Wait for the gumball to be despensed" << std::endl;

			break;
		case State::SoldOut:
			std::cout << "Quarter returned (" << m_quarterCount << ")" << std::endl;
			m_quarterCount = 0;

			break;
		}
	}

	void TurnCrank()
	{
		switch (m_state)
		{
		case State::SoldOut:
			std::cout << "You turned but there's no gumballs" << std::endl;

			break;
		case State::NoQuarter:
			std::cout << "You turned but there's no quarter" << std::endl;

			break;
		case State::MaxQuarters:
		case State::HasQuarter:
			std::cout << "You turned" << std::endl;
			m_state = State::Sold;

			if (m_quarterCount > 0)
			{
				--m_quarterCount;
			}

			Dispense();

			break;
		case State::Sold:
			std::cout << "Turning twice doesn't get you another gumball" << std::endl;

			break;
		}
	}


	std::string ToString() const
	{
		return "Best C++ gumball Machine\nGumballs count: " + std::to_string(m_count) + "\nQuarters count: " +
			std::to_string(m_quarterCount) + "\nMachine state: " + m_stateDescriptions.at(m_state);
	}

private:
	void Dispense()
	{
		switch (m_state)
		{
		case State::Sold:
			std::cout << "A gumball comes rolling out the slot" << std::endl;
			--m_count;

			if (m_count == 0)
			{
				std::cout << "Oops, out of gumballs" << std::endl;
				m_state = State::SoldOut;

				return;
			}

			m_state = m_quarterCount > 0 ? State::HasQuarter : State::NoQuarter;

			break;
		case State::NoQuarter:
			std::cout << "You need to pay first" << std::endl;

			break;
		case State::MaxQuarters:
		case State::SoldOut:
		case State::HasQuarter:
			std::cout << "No gumball dispensed" << std::endl;

			break;
		}
	}

	unsigned int m_count = 0;
	unsigned int m_quarterCount = 0;
	std::map<State, std::string> m_stateDescriptions = {
		{State::NoQuarter, "waiting for quarter"},
		{State::HasQuarter, "waiting for turning the crank"},
		{State::MaxQuarters, "Quarters count is full. Waiting for turning the crank"},
		{State::Sold, "delivering a gumball"},
		{State::SoldOut, "sold out"},
	};
	State m_state;
};