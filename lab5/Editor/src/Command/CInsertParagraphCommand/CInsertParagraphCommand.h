#pragma once
#include "../CAbstractCommand/CAbstractCommand.h"
#include <string>

class CInsertParagraphCommand : public CAbstractCommand
{
public:
	CInsertParagraphCommand(const std::string& text);

	void DoExecute() override;

	void DoUnexecute() override;

private:
	std::string m_text;
};
