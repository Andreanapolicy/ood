#pragma once
#include "../CAbstractCommand/CAbstractCommand.h"
#include "../../Content/Exception/WrongImageSizeException.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& currentWidth, int& currentHeight, int newWidth, int newHeight);

private:
	void DoExecute() override;

	void DoUnexecute() override;

	int& m_currentWidth;
	int& m_currentHeight;

	int m_newWidth;
	int m_newHeight;
};