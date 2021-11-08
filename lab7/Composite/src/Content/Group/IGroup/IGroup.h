#pragma once
#include "../../Composite/IComposite/IComposite.h"
#include "../../Shape/IShape/IShape.h"

class IGroup : public IShape, public IComposite
{
};