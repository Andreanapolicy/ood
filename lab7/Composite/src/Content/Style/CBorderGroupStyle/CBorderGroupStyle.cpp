#include "CBorderGroupStyle.h"

CBorderGroupStyle::CBorderGroupStyle(BorderGroupEnumerator& enumerator)
	: m_enumerator(enumerator)
{
}

void CBorderGroupStyle::SetThickness(double thickness)
{
	BorderStyleEnumerator styleEnumerator = [thickness](IBorderStyle& style) {
		style.SetThickness(thickness);
	};

	m_enumerator(styleEnumerator);
}

std::optional<double> CBorderGroupStyle::GetThickness() const
{
	std::optional<double> thickness = std::nullopt;
	bool isRepeatedly = false;

	BorderStyleEnumerator styleEnumerator = [&thickness, &isRepeatedly](IBorderStyle& style) {
		if (!isRepeatedly)
		{
			thickness = style.GetThickness();
			isRepeatedly = true;
		}

		if (thickness != style.GetThickness())
		{
			thickness = std::nullopt;
		}
	};

	m_enumerator(styleEnumerator);

	return thickness;
}

bool CBorderGroupStyle::isEnable() const
{
	bool isEnable = false;
	bool isRepeatedly = false;

	BorderStyleEnumerator styleEnumerator = [&isEnable, &isRepeatedly](IBorderStyle& style) {
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
	BorderStyleEnumerator styleEnumerator = [](IBorderStyle& style) {
		style.Enable();
	};

	m_enumerator(styleEnumerator);
}

void CBorderGroupStyle::Disable()
{
	BorderStyleEnumerator styleEnumerator = [](IBorderStyle& style) {
		style.Disable();
	};

	m_enumerator(styleEnumerator);
}

std::optional<Color> CBorderGroupStyle::GetColor() const
{
	std::optional<Color> color = std::nullopt;
	bool isRepeatedly = false;

	BorderStyleEnumerator styleEnumerator = [&color, &isRepeatedly](IBorderStyle& style) {
		if (!isRepeatedly)
		{
			color = style.GetColor();
			isRepeatedly = true;
		}

		if (color != style.GetColor())
		{
			color = std::nullopt;
		}
	};

	m_enumerator(styleEnumerator);

	return color;
}

void CBorderGroupStyle::SetColor(Color color)
{
	BorderStyleEnumerator styleEnumerator = [color](IBorderStyle& style) {
		style.SetColor(color);
	};

	m_enumerator(styleEnumerator);
}
