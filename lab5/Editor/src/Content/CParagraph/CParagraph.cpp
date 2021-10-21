#include "CParagraph.h"

CParagraph::CParagraph(const std::string& text, CHistory& history)
	: m_text(text)
	, m_history(history)
{

}

void CParagraph::SetText(const std::string& text)
{
	m_history.AddAndExecuteCommand(std::make_unique<CReplaceTextParagraphCommand>(m_text, text));
}

std::string CParagraph::GetText() const
{
	return m_text;
}