#include "CInsertDocumentItemCommand.h"

CInsertDocumentItemCommand::CInsertDocumentItemCommand(std::vector<CDocumentItem>& items, CDocumentItem& newItem, size_t index)
	: m_items(items)
 	, m_newItem(newItem)
 	, m_index(index)
{
	if (index > items.size())
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
	m_items.erase(m_items.begin() + m_index);
}

CInsertDocumentItemCommand::~CInsertDocumentItemCommand()
{
	if (!IsExecuted() && m_newItem.GetImage())
	{
		m_newItem.GetImage()->Remove();
	}
}
