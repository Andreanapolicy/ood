#include "CParagraph.h"

CParagraph::CParagraph(const std::string& text)
	: m_text(text)
{

}

void CParagraph::SetText(const std::string& text)
{
	m_text = text;
}

std::string CParagraph::GetText() const
{
	return m_text;
}