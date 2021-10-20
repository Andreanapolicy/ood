#pragma once
#include "../CAbstractCommand/CAbstractCommand.h"
#include <string>

class CReplaceTextParagraphCommand : public CAbstractCommand
{
public:
	CReplaceTextParagraphCommand(std::string& oldText, std::string const& newText);

private:
	void DoExecute() override;

	void DoUnexecute() override;

	std::string& m_oldText;
	std::string m_newText;
};
