#pragma once
#include "../ICanvas/ICanvas.h"
#include "SFML/Graphics.hpp"
#include <cmath>

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderTarget& renderTarget);

	void DrawLine(PointD from, PointD to, Color borderColor, double thickness) override;

	void FillPolygon(const std::vector<PointD>& points, Color fillColor) override;

	void DrawEllipse(PointD center, double widthRadius, double heightRadius, Color fillColor, Color borderColor, double thickness) override;

private:
	sf::RenderTarget& m_renderTarget;
};
