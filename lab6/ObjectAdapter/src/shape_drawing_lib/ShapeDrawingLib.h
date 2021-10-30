#pragma once
#include "../graphics_lib/GraphicsLib.h"

namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;

	virtual ~ICanvasDrawable() = default;
};

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point& p1, const Point& p2, const Point& p3)
		: m_firstVertex(p1)
		, m_secondVertex(p2)
		, m_thirdVertex(p3)
	{
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.MoveTo(m_firstVertex.x, m_firstVertex.y);
		canvas.LineTo(m_secondVertex.x, m_secondVertex.y);
		canvas.LineTo(m_thirdVertex.x, m_thirdVertex.y);
		canvas.LineTo(m_firstVertex.x, m_thirdVertex.y);
	}

private:
	Point m_firstVertex;
	Point m_secondVertex;
	Point m_thirdVertex;
};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point& leftTop, int width, int height)
		: m_leftTopVertex(leftTop)
		, m_width(width)
		, m_height(height)
	{
	}

	void Draw(graphics_lib::ICanvas& canvas) const override
	{
		canvas.MoveTo(m_leftTopVertex.x, m_leftTopVertex.y);

		canvas.LineTo(m_leftTopVertex.x + m_width, m_leftTopVertex.y);
		canvas.LineTo(m_leftTopVertex.x + m_width, m_leftTopVertex.y - m_height);
		canvas.LineTo(m_leftTopVertex.x, m_leftTopVertex.y - m_height);
		canvas.LineTo(m_leftTopVertex.x, m_leftTopVertex.y);
	}

private:
	Point m_leftTopVertex;
	int m_width;
	int m_height;
};

class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas& canvas)
		: m_canvas(canvas)
	{
	}

	void Draw(const ICanvasDrawable& drawable)
	{
		drawable.Draw(m_canvas);
	}

private:
	graphics_lib::ICanvas& m_canvas;
};
}