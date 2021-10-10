#pragma once
#include "../PictureDraft/CPictureDraft.h"
#include "../Canvas/ICanvas.h"

class CPainter
{
public:
	void static DrawPicture(const CPictureDraft& pictureDraft, ICanvas& canvas)
	{
		for (auto index = 0; index < pictureDraft.GetShapesCount(); index ++)
		{
			pictureDraft.GetShape(index).Draw(canvas);
		}
	}
};