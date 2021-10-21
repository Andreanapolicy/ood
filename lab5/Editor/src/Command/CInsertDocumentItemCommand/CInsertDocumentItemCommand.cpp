#include "CInsertDocumentItemCommand.h"
#include "../Exception/CWrongIndexOfItemInDocumentException/CWrongIndexOfItemInDocumentException.h"

CInsertDocumentItemCommand::CInsertDocumentItemCommand(CDocumentItem& newItem, std::vector<CDocumentItem>& items, size_t index)
	: m_items(items)
 	, m_newItem(newItem)
 	, m_index(index)
{
	if (index >= items.size())
	{
		throw CWrongIndexOfItemInDocumentException("Error, index greater then document size");
	}
}

void CInsertDocumentItemCommand::DoExecute()
{
	m_items.emplace(m_items.begin() + m_index, m_newItem);
}

void CInsertDocumentItemCommand::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_index, m_newItem);
}

CInsertDocumentItemCommand::~CInsertDocumentItemCommand()
{
	if (m_newItem.GetImage() && !IsExecuted())
	{
		m_newItem.GetImage()->Remove();
	}
}
