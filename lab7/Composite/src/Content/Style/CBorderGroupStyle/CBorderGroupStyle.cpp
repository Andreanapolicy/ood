#include "CBorderGroupStyle.h"

CBorderGroupStyle::CBorderGroupStyle(BorderGroupEnumerator& enumerator)
	: m_enumerator(enumerator)
{
}

void CBorderGroupStyle::SetThickness(double thickness)
{
	BorderStyleEnumerator styleEnumerator = [&](IBorderStyle& style) {
		style.SetThickness(thickness);
	};

	m_enumerator(styleEnumerator);
}

double CBorderGroupStyle::GetThickness() const
{
	double thickness = 0;
	bool isRepeatedly = false;

	BorderStyleEnumerator styleEnumerator = [&](IBorderStyle& style) {
		if (!isRepeatedly)
		{
			thickness = style.GetThickness();
			isRepeatedly = true;
		}

		if (thickness != style.GetThickness())
		{
			thickness = 0;
		}
	};

	m_enumerator(styleEnumerator);

	return thickness;
}

bool CBorderGroupStyle::isEnable() const
{
	bool isEnable = false;
	bool isRepeatedly = false;

	BorderStyleEnumerator styleEnumerator = [&](IBorderStyle& style) {
		if (!isRepeatedly)
		{
			isEnable = style.isEnable();
			isRepeatedly = true;
		}

		if (isEnable != style.isEnable())
		{
			isEnable = false;
		}
	};

	m_enumerator(styleEnumerator);

	return isEnable;
}

void CBorderGroupStyle::Enable()
{
	BorderStyleEnumerator styleEnumerator = [&](IBorderStyle& style) {
		style.Enable();
	};

	m_enumerator(styleEnumerator);
}

void CBorderGroupStyle::Disable()
{
	BorderStyleEnumerator styleEnumerator = [&](IBorderStyle& style) {
		style.Disable();
	};

	m_enumerator(styleEnumerator);
}

Color CBorderGroupStyle::GetColor() const
{
	uint32_t color = 0x00000000;
	bool isRepeatedly = false;

	BorderStyleEnumerator styleEnumerator = [&](IBorderStyle& style) {
		if (!isRepeatedly)
		{
			color = style.GetColor();
			isRepeatedly = true;
		}

		if (color != style.GetColor())
		{
			color = 0x00000000;
		}
	};

	m_enumerator(styleEnumerator);

	return color;
}

void CBorderGroupStyle::SetColor(Color color)
{
	BorderStyleEnumerator styleEnumerator = [&](IBorderStyle& style) {
		style.SetColor(color);
	};

	m_enumerator(styleEnumerator);
}
