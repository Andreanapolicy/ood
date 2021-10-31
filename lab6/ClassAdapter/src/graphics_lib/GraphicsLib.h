#pragma once
#include <iostream>

namespace graphics_lib
{
class ICanvas
{
public:
	virtual void MoveTo(int x, int y) = 0;

	virtual void LineTo(int x, int y) = 0;

	virtual ~ICanvas() = default;
};

class CCanvas : public ICanvas
{
public:
	void MoveTo(int x, int y) override
	{
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}

	void LineTo(int x, int y) override
	{
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
};
}