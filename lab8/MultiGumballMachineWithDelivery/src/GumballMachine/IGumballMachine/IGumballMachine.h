#pragma once

constexpr int maxQuarterCount = 5;

class IGumballMachine
{
public:
	virtual void ReleaseBall() = 0;

	virtual void ReleaseQuarter(unsigned int count = 1) = 0;

	virtual void AddQuarter() = 0;

	virtual void AddBalls(unsigned int count) = 0;

	virtual unsigned int GetBallsCount() const = 0;

	virtual unsigned int GetQuartersCount() const = 0;

	virtual void SetSoldOutState() = 0;

	virtual void SetNoQuarterState() = 0;

	virtual void SetSoldState() = 0;

	virtual void SetHasQuarterState() = 0;

	virtual void SetMaxQuarterCountState() = 0;

	virtual ~IGumballMachine() = default;
};
