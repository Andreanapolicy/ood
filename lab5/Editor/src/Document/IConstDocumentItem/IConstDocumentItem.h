#pragma once
#include <memory>
#include "../../Content/IParagraph/IParagraph.h"
#include "../../Content/IImage/IImage.h"

class IConstDocumentItem
{
public:
	virtual std::shared_ptr<const IImage> GetImage() const = 0;

	virtual std::shared_ptr<const IParagraph> GetParagraph() const = 0;

	virtual ~IConstDocumentItem() = default;
};