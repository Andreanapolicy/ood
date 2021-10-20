#pragma once
#include "../CAbstractCommand/CAbstractCommand.h"
#include <string>

class CChangeTitleCommand : public CAbstractCommand
{
public:
	CChangeTitleCommand(std::string& m_oldTitle, std::string const& m_newTitle);

private:
	void DoExecute() override;

	void DoUnexecute() override;

	std::string& m_oldTitle;
	std::string m_newTitle;
};