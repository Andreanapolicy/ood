#pragma once
#include "../ICanvas/ICanvas.h"
#include "SFML/Graphics.hpp"
#include <cmath>

class CCanvas : public ICanvas
{
public:
	explicit CCanvas(sf::RenderTarget& renderTarget);

	void DrawLine(PointD from, PointD to, Color borderColor, double thickness) override;

	void FillPolygon(const std::vector<PointD>& points, Color fillColor) override;

	void DrawEllipse(PointD center, double widthRadius, double heightRadius, Color borderColor, double thickness) override;

	void FillEllipse(PointD center, double widthRadius, double heightRadius, Color fillColor) override;

private:

	void DrawEllipseWithColor(PointD center, double widthRadius, double heightRadius, sf::Color fillColor, sf::Color borderColor, double thickness);
	sf::RenderTarget& m_renderTarget;
};
