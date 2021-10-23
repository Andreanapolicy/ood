#pragma once
#include "../../Document/IDocument/IDocument.h"

class IStorage
{
public:
	virtual void Save(const std::string& path, IDocument& document) = 0;

	virtual ~IStorage() = default;
};