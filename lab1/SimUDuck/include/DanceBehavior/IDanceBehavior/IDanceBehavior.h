#pragma once

class IDanceBehavior
{
public:
	virtual ~IDanceBehavior() = default;
	virtual void Dance() = 0;
};
