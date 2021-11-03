#include "CBorderStyle.h"

CBorderStyle::CBorderStyle()
	: m_enable(false)
	, m_color(0)
	, m_thickness(0)
{
}

void CBorderStyle::SetThickness(double thickness)
{
	m_thickness = thickness;
}

double CBorderStyle::GetThickness() const
{
	return m_thickness;
}

bool CBorderStyle::isEnable() const
{
	return m_enable;
}

void CBorderStyle::Enable()
{
	m_enable = true;
}

void CBorderStyle::Disable()
{
	m_enable = false;
}

Color CBorderStyle::GetColor() const
{
	return m_color;
}

void CBorderStyle::SetColor(Color color)
{
	m_color = color;
}
