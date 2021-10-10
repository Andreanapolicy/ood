#pragma once
#include <sstream>
#include "../PictureDraft/CPictureDraft.h"

class IDesigner
{
public:
	virtual CPictureDraft CreateDraft(std::istream& input) const = 0;

	virtual ~IDesigner() = default;
};