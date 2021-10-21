#pragma once
#include "../CAbstractCommand/CAbstractCommand.h"
#include "../../Document/CDocumentItem/CDocumentItem.h"
#include <vector>

class CInsertDocumentItemCommand : public CAbstractCommand
{
public:
	CInsertDocumentItemCommand(CDocumentItem& newItem, std::vector<CDocumentItem>& items, size_t index);

	~CInsertDocumentItemCommand();

private:
	void DoExecute() override;

	void DoUnexecute() override;

	CDocumentItem& m_newItem;
	std::vector<CDocumentItem>& m_items;
	size_t m_index;
};