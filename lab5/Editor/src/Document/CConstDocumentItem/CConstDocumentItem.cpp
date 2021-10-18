#include "CConstDocumentItem.h"

CConstDocumentItem::CConstDocumentItem(std::variant<std::shared_ptr<const IImage>, std::shared_ptr<const IParagraph>>&& item)
	: m_item(std::move(item))
{
}

std::shared_ptr<const IImage> CConstDocumentItem::GetImage()
{

	return std::holds_alternative<std::shared_ptr<const IImage>>(m_item)
		? std::get<std::shared_ptr<const IImage>>(m_item)
		: nullptr;
}

std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph()
{
	return std::holds_alternative<std::shared_ptr<const IParagraph>>(m_item)
		? std::get<std::shared_ptr<const IParagraph>>(m_item)
		: nullptr;
}
