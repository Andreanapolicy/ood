#pragma once
#include "../CAbstractCommand/CAbstractCommand.h"
#include <string>

class CReplaceTextParagraphCommand : public CAbstractCommand
{
public:
	CReplaceTextParagraphCommand(std::string& currentText, std::string const& newText);

private:
	void DoExecute() override;

	void DoUnexecute() override;

	std::string& m_currentText;
	std::string m_newText;
};
