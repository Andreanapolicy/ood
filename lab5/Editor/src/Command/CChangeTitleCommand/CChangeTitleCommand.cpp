#include "CChangeTitleCommand.h"

CChangeTitleCommand::CChangeTitleCommand(std::string& currentTitle, const std::string& newTitle)
	: m_currentTitle(currentTitle)
	, m_newTitle(newTitle)
{
}

void CChangeTitleCommand::DoExecute()
{
	std::swap(m_currentTitle, m_newTitle);
}

void CChangeTitleCommand::DoUnexecute()
{
	std::swap(m_currentTitle, m_newTitle);
}
