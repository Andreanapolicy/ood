#pragma once
#include "../IParagraph/IParagraph.h"
#include "../../History/CHistory/CHistory.h"
#include "../../Command/CReplaceTextParagraphCommand/CReplaceTextParagraphCommand.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(const std::string& text, CHistory& history);

	void SetText(const std::string& text) override;

	std::string GetText() const override;

private:
	std::string m_text;
	CHistory& m_history;
};