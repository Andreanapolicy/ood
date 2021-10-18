#pragma once
#include <memory>
#include "../../Content/IParagraph/IParagraph.h"
#include "../../Content/IImage/IImage.h"

class IDocumentItem
{
public:
	virtual std::shared_ptr<IImage> GetImage() = 0;

	virtual std::shared_ptr<IParagraph> GetParagraph() = 0;

	virtual ~IDocumentItem() = default;
};