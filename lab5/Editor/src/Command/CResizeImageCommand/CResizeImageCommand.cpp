#include "CResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(int& currentWidth, int& currentHeight, int newWidth, int newHeight)
	: m_currentWidth(currentWidth)
	, m_currentHeight(currentHeight)
{
	if (newWidth < 1 || newWidth > 10000 || newHeight < 1 || newHeight > 10000 )
	{
		throw WrongImageSizeException("Error, wrong image size(should be [1, 10000])");
	}

	m_newWidth = newWidth;
	m_newHeight = newHeight;
}

void CResizeImageCommand::DoExecute()
{
	std::swap(m_currentWidth, m_newWidth);
	std::swap(m_currentHeight, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	std::swap(m_currentWidth, m_newWidth);
	std::swap(m_currentHeight, m_newHeight);
}
