#include "CFillGroupStyle.h"

CFillGroupStyle::CFillGroupStyle(FillGroupEnumerator& fillGroupEnumerator)
	: m_enumerator(fillGroupEnumerator)
{
}

bool CFillGroupStyle::isEnable() const
{
	bool isEnable = false;
	bool isRepeatedly = false;

	StyleEnumerator styleEnumerator = [&](IStyle& style) {
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

void CFillGroupStyle::Enable()
{
	StyleEnumerator styleEnumerator = [&](IStyle& style) {
		style.Enable();
	};

	m_enumerator(styleEnumerator);
}

void CFillGroupStyle::Disable()
{
	StyleEnumerator styleEnumerator = [&](IStyle& style) {
		style.Disable();
	};

	m_enumerator(styleEnumerator);
}

Color CFillGroupStyle::GetColor() const
{
	uint32_t color = 0x00000000;
	bool isRepeatedly = false;

	StyleEnumerator styleEnumerator = [&](IStyle& style) {
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

void CFillGroupStyle::SetColor(Color color)
{
	StyleEnumerator styleEnumerator = [&](IStyle& style) {
		style.SetColor(color);
	};

	m_enumerator(styleEnumerator);
}
