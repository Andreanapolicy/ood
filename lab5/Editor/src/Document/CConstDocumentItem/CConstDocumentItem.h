#pragma once
#include "../IConstDocumentItem/IConstDocumentItem.h"
#include <variant>

class CConstDocumentItem : public IConstDocumentItem
{
public:
	CConstDocumentItem(std::variant<std::shared_ptr<const IImage>, std::shared_ptr<const IParagraph>>&& item);

	std::shared_ptr<const IImage> GetImage() override;

	std::shared_ptr<const IParagraph> GetParagraph() override;

private:
	std::variant<std::shared_ptr<const IImage>, std::shared_ptr<const IParagraph>> m_item;
};