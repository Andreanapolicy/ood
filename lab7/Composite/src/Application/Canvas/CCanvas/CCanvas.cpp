#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderTarget& renderTarget)
	: m_renderTarget(renderTarget)
{
}

void CCanvas::DrawLine(PointD from, PointD to, Color borderColor, double thickness)
{
	sf::Vertex vertices[4];

	sf::Vector2f fromVector((float)from.x, (float)from.y);
	sf::Vector2f toVector((float)from.x, (float)from.y);

	sf::Vector2f direction = fromVector - toVector;
	sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

	sf::Vector2f offset = (float)(thickness / 2.f) * unitPerpendicular;

	vertices[0].position = fromVector + offset;
	vertices[1].position = toVector + offset;
	vertices[2].position = toVector - offset;
	vertices[3].position = fromVector - offset;

	for (auto& vertex : vertices)
	{
		vertex.color = sf::Color(borderColor);
	}

	m_renderTarget.draw(vertices, 4, sf::Quads);
}

void CCanvas::FillPolygon(const std::vector<PointD>& points, Color fillColor)
{
	sf::ConvexShape shape;
	shape.setPointCount(points.size());

	for (size_t index = 0; index < points.size(); index++)
	{
		shape.setPoint(index, sf::Vector2f((float)points[index].x, (float)points[index].y));
	}

	shape.setFillColor(sf::Color(fillColor));
	shape.setOutlineColor(sf::Color(fillColor));

	m_renderTarget.draw(shape);
}

void CCanvas::DrawEllipse(PointD center, double widthRadius, double heightRadius, Color borderColor, double thickness)
{
	DrawEllipseWithColor(
		center,
		widthRadius,
		heightRadius,
		sf::Color(0, 0, 0, 0),
		sf::Color(borderColor),
		thickness);
}

void CCanvas::FillEllipse(PointD center, double widthRadius, double heightRadius, Color fillColor)
{
	DrawEllipseWithColor(
		center,
		widthRadius,
		heightRadius,
		sf::Color(fillColor),
		sf::Color(0, 0, 0, 0),
		0);
}

void CCanvas::DrawEllipseWithColor(PointD center, double widthRadius, double heightRadius, sf::Color fillColor, sf::Color borderColor, double thickness)
{
	sf::CircleShape circleShape((float)widthRadius);

	circleShape.setOrigin((float)widthRadius, (float)widthRadius);
	circleShape.move(sf::Vector2f((float)center.x, (float)m_renderTarget.getSize().y - (float)center.y));
	circleShape.setScale(1.f, (float)heightRadius / (float)widthRadius);

	circleShape.setOutlineColor(borderColor);
	circleShape.setOutlineThickness((float)thickness);
	circleShape.setFillColor(fillColor);

	m_renderTarget.draw(circleShape);
}
