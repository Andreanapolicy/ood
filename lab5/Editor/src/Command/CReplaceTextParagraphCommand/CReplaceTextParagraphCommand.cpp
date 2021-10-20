#include "CReplaceTextParagraphCommand.h"

CReplaceTextParagraphCommand::CReplaceTextParagraphCommand(std::string& oldText, const std::string& newText)
	: m_oldText(oldText)
	, m_newText(newText)
{
}

void CReplaceTextParagraphCommand::DoExecute()
{
	std::swap(m_oldText, m_newText);
}

void CReplaceTextParagraphCommand::DoUnexecute()
{
	std::swap(m_oldText, m_newText);
}
