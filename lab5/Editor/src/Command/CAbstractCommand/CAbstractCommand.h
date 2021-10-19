#include "../ICommand/ICommand.h"

class CAbstractCommand : public ICommand
{
public:
	void Execute() override;
	void Unexecute() override;
	bool IsExecuted() const;

protected:
	virtual void DoExecute() = 0;
	virtual void DoUnexecute() = 0;

private:
	bool m_isExecuted = false;
};
