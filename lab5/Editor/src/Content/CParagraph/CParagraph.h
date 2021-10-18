#pragma once

#include "../IParagraph/IParagraph.h"
class CParagraph : public IParagraph
{
public:
	CParagraph(const std::string& text);

	void SetText(const std::string& text) override;

	std::string GetText() const override;

private:
	std::string m_text;
};