#pragma once
#include "../IDocumentItem/IDocumentItem.h"
#include <variant>

class CDocumentItem : public IDocumentItem
{
public:
	CDocumentItem(std::variant<std::shared_ptr<IImage>, std::shared_ptr<IParagraph>>&& item);

	std::shared_ptr<IImage> GetImage() override;

	std::shared_ptr<IParagraph> GetParagraph() override;

private:
	std::variant<std::shared_ptr<IImage>, std::shared_ptr<IParagraph>> m_item;
};
