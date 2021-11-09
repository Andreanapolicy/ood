#include "CFillStyle.h"

CFillStyle::CFillStyle()
	: m_enable(false)
	, m_color(0)
{
}

bool CFillStyle::isEnable() const
{
	return m_enable;
}

void CFillStyle::Enable()
{
	m_enable = true;
}

void CFillStyle::Disable()
{
	m_enable = false;
}

std::optional<Color> CFillStyle::GetColor() const
{
	return m_color;
}

void CFillStyle::SetColor(Color color)
{
	m_color = color;
}
