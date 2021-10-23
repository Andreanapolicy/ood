#pragma once
#include "../../Document/CDocumentItem/CDocumentItem.h"
#include "../CAbstractCommand/CAbstractCommand.h"
#include "../Exception/CWrongIndexOfItemInDocumentException/CWrongIndexOfItemInDocumentException.h"
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