#pragma once
#include "../../../src/Command/CAbstractCommand/CAbstractCommand.h"

class CTestCommand : public CAbstractCommand
{
public:
	void DoExecute() override
	{
	}

	void DoUnexecute() override
	{
	}
};