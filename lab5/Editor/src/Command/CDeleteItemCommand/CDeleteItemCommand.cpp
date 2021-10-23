#include "CDeleteItemCommand.h"

CDeleteItemCommand::CDeleteItemCommand(std::vector<CDocumentItem>& items, size_t index)
	: m_items(items)
	, m_index(index)
{
	if (m_index >= m_items.size())
	{
		throw CWrongIndexOfItemInDocumentException("Index cannot be greater than number of elements");
	}

	m_item = std::make_shared<CDocumentItem>(m_items.at(index));
}

void CDeleteItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_index);
}

void CDeleteItemCommand::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_index, *m_item);
}

CDeleteItemCommand::~CDeleteItemCommand()
{
	if (IsExecuted() && m_item->GetImage())
	{
		m_item->GetImage()->Remove();
	}
}