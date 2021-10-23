#pragma once
#include "../IConstDocumentItem/IConstDocumentItem.h"
#include <variant>

class CConstDocumentItem : public IConstDocumentItem
{
public:
	CConstDocumentItem(std::variant<std::shared_ptr<IImage>, std::shared_ptr<IParagraph>>&& item);

	std::shared_ptr<const IImage> GetImage() const override;

	std::shared_ptr<const IParagraph> GetParagraph() const override;

protected:
	std::variant<std::shared_ptr<IImage>, std::shared_ptr<IParagraph>> m_item;
};