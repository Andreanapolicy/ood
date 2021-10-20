#pragma once
#include "../CAbstractCommand/CAbstractCommand.h"
#include <string>

class CChangeTitleCommand : public CAbstractCommand
{
public:
	CChangeTitleCommand(std::string& currentTitle, std::string const& newTitle);

private:
	void DoExecute() override;

	void DoUnexecute() override;

	std::string& m_currentTitle;
	std::string m_newTitle;
};