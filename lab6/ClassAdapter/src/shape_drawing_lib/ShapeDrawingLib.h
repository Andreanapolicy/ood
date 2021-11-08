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
	CTriangle(const Point& firstVertex, const Point& secondVertex, const Point& thirdVertex)
		: m_firstVertex(firstVertex)
		, m_secondVertex(secondVertex)
		, m_thirdVertex(thirdVertex)
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
	CRectangle(const Point& leftTop, const int width, const int height)
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
	explicit CCanvasPainter(graphics_lib::ICanvas& canvas)
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