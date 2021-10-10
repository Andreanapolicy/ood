#pragma once
#include "./ICanvas.h"
#include "../Color/Color.h"
#include "SFML/Graphics.hpp"

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderTarget& renderTarget)
		: m_renderTarget(renderTarget)
	{
	}

	void SetColor(const Color& color) override
	{
		switch (color)
		{
		case Color::Green:
			m_color = sf::Color::Green;
			break;
		case Color::Red:
			m_color = sf::Color::Red;
			break;
		case Color::Blue:
			m_color = sf::Color::Blue;
			break;
		case Color::Yellow:
			m_color = sf::Color::Yellow;
			break;
		case Color::Pink:
			m_color = sf::Color(255, 20, 148);
			break;
		case Color::Black:
			m_color = sf::Color::Black;
			break;
		}
	}

	void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) override
	{
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f((float)fromPoint.getX(), (float)m_renderTarget.getSize().y - (float)fromPoint.getY())),
			sf::Vertex(sf::Vector2f((float)toPoint.getX(), (float)m_renderTarget.getSize().y - (float)toPoint.getY())),
		};

		line[0].color = m_color;
		line[1].color = m_color;
		m_renderTarget.draw(line, 2, sf::Lines);
	}

	void DrawEllipse(const CPoint& centerPoint, const int widthRadius, const int heightRadius) override
	{
		sf::CircleShape circleShape((float)widthRadius);

		circleShape.setOrigin((float)widthRadius, (float)widthRadius);
		circleShape.move(sf::Vector2f((float)centerPoint.getX(), (float)m_renderTarget.getSize().y - (float)centerPoint.getY()));
		circleShape.setScale(1.f, float(heightRadius / widthRadius));
		circleShape.setOutlineColor(m_color);
		circleShape.setOutlineThickness(3.f);
		circleShape.setFillColor(sf::Color::White);

		m_renderTarget.draw(circleShape);
	}

private:
	sf::RenderTarget& m_renderTarget;
	sf::Color m_color;
};