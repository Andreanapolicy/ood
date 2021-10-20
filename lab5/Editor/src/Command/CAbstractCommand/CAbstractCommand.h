#pragma once
#include "../ICommand/ICommand.h"

class CAbstractCommand : public ICommand
{
public:
	void Execute() final;
	void Unexecute() final;

protected:
	virtual void DoExecute() = 0;
	virtual void DoUnexecute() = 0;
	bool IsExecuted() const;

private:
	bool m_isExecuted = false;
};
