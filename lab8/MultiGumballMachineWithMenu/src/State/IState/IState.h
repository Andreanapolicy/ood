#pragma once
#include <string>

class IState
{
public:
	virtual void InsertQuarter() = 0;

	virtual void InsertBalls(unsigned int count) = 0;

	virtual void EjectQuarter() = 0;

	virtual void TurnCrank() = 0;

	virtual void Dispense() = 0;

	virtual std::string ToString() const = 0;

	virtual ~IState() = default;
};