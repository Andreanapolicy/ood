#pragma once
#include "../CConstDocumentItem/CConstDocumentItem.h"
#include <variant>

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(std::variant<std::shared_ptr<IImage>, std::shared_ptr<IParagraph>>&& item);

	std::shared_ptr<IImage> GetImage();

	std::shared_ptr<IParagraph> GetParagraph();
};
