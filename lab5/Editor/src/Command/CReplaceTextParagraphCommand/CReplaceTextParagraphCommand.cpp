#include "CReplaceTextParagraphCommand.h"

CReplaceTextParagraphCommand::CReplaceTextParagraphCommand(std::string& currentText, const std::string& newText)
	: m_currentText(currentText)
	, m_newText(newText)
{
}

void CReplaceTextParagraphCommand::DoExecute()
{
	std::swap(m_currentText, m_newText);
}

void CReplaceTextParagraphCommand::DoUnexecute()
{
	std::swap(m_currentText, m_newText);
}
