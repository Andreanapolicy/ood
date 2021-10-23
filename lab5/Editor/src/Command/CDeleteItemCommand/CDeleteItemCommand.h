#include "../../Document/CDocumentItem/CDocumentItem.h"
#include "../CAbstractCommand/CAbstractCommand.h"
#include "../Exception/CWrongIndexOfItemInDocumentException/CWrongIndexOfItemInDocumentException.h"
#include <vector>

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<CDocumentItem>& items, size_t index);

	~CDeleteItemCommand();

private:
	void DoExecute() override;

	void DoUnexecute() override;

	std::vector<CDocumentItem>& m_items;
	size_t m_index;
	std::shared_ptr<CDocumentItem> m_item;
};
