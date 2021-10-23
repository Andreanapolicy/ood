#include "CDocumentItem.h"

CDocumentItem::CDocumentItem(std::variant<std::shared_ptr<IImage>, std::shared_ptr<IParagraph>>&& item)
	: CConstDocumentItem(std::move(item))
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return std::holds_alternative<std::shared_ptr<IImage>>(m_item)
		? std::get<std::shared_ptr<IImage>>(m_item)
		: nullptr;
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return std::holds_alternative<std::shared_ptr<IParagraph>>(m_item)
		? std::get<std::shared_ptr<IParagraph>>(m_item)
		: nullptr;
}
