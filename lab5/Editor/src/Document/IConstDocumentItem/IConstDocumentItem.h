#pragma once
#include <memory>
#include "../../Content/IParagraph/IParagraph.h"
#include "../../Content/IImage/IImage.h"

class IConstDocumentItem
{
public:
	virtual std::shared_ptr<const IImage> GetImage() = 0;

	virtual std::shared_ptr<const IParagraph> GetParagraph() = 0;

	virtual ~IConstDocumentItem() = default;
};