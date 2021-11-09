#include "CFillGroupStyle.h"

CFillGroupStyle::CFillGroupStyle(FillGroupEnumerator& fillGroupEnumerator)
	: m_enumerator(fillGroupEnumerator)
{
}

bool CFillGroupStyle::isEnable() const
{
	bool isEnable = false;
	bool isRepeatedly = false;

	StyleCallback StyleCallback = [&isEnable, &isRepeatedly](IStyle& style) {
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

	m_enumerator(StyleCallback);

	return isEnable;
}

void CFillGroupStyle::Enable()
{
	StyleCallback StyleCallback = [](IStyle& style) {
		style.Enable();
	};

	m_enumerator(StyleCallback);
}

void CFillGroupStyle::Disable()
{
	StyleCallback StyleCallback = [](IStyle& style) {
		style.Disable();
	};

	m_enumerator(StyleCallback);
}

Color CFillGroupStyle::GetColor() const //color|null
{
	Color color = 0x00000000;
	bool isRepeatedly = false;

	StyleCallback StyleCallback = [&color, &isRepeatedly](IStyle& style) {
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

	m_enumerator(StyleCallback);

	return color;
}

void CFillGroupStyle::SetColor(Color color)
{
	StyleCallback StyleCallback = [color](IStyle& style) {
		style.SetColor(color);
	};

	m_enumerator(StyleCallback);
}
