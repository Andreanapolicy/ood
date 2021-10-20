#include "CChangeTitleCommand.h"

CChangeTitleCommand::CChangeTitleCommand(std::string& oldTitle, const std::string& newTitle)
	: m_oldTitle(oldTitle)
	, m_newTitle(newTitle)
{
}

void CChangeTitleCommand::DoExecute()
{
	std::swap(m_oldTitle, m_newTitle);
}

void CChangeTitleCommand::DoUnexecute()
{
	std::swap(m_oldTitle, m_newTitle);
}
