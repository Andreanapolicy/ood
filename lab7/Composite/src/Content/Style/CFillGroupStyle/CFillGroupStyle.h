#pragma once
#include "../IStyle/IStyle.h"

typedef std::function<void(StyleEnumerator)> FillGroupEnumerator;

class CFillGroupStyle : public IStyle
{
public:
	CFillGroupStyle(FillGroupEnumerator& fillGroupEnumerator);

	bool isEnable() const override;

	void Enable() override;

	void Disable() override;

	Color GetColor() const override;

	void SetColor(Color color) override;

private:
	FillGroupEnumerator m_enumerator;
};
