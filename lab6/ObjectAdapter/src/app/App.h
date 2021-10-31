#pragma once
#include "../modern_graphics_lib/ModernGraphicsLib.h"
#include "../shape_drawing_lib/ShapeDrawingLib.h"
#include <iostream>

namespace app
{
class CModernGraphicsLibAdapter : public graphics_lib::ICanvas
{
public:
	CModernGraphicsLibAdapter(modern_graphics_lib::CModernGraphicsRenderer& modernGraphicsRenderer)
		: m_modernGraphicsRenderer(modernGraphicsRenderer)
	{
	}

	void MoveTo(int x, int y) override
	{
		m_startPoint = {x, y};
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint m_endPoint = {x, y};
		m_modernGraphicsRenderer.DrawLine(m_startPoint, m_endPoint);

		m_startPoint = m_endPoint;
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_modernGraphicsRenderer;
	modern_graphics_lib::CPoint m_startPoint = {0, 0};
};

void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	shape_drawing_lib::CRectangle rectangle({100, 50}, 50, 50);
	painter.Draw(rectangle);

	shape_drawing_lib::CTriangle triangle({100, 50}, {125, 100}, {150, 50});
	painter.Draw(triangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas canvas;
	shape_drawing_lib::CCanvasPainter canvasPainter(canvas);

	PaintPicture(canvasPainter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);

	CModernGraphicsLibAdapter canvas(renderer);
	shape_drawing_lib::CCanvasPainter canvasPainter(canvas);

	PaintPicture(canvasPainter);
}
}