#pragma once
#include "../IStyle/IStyle.h"

typedef std::function<void(StyleCallback)> FillGroupEnumerator;

class CFillGroupStyle : public IStyle
{
public:
	CFillGroupStyle(FillGroupEnumerator& fillGroupEnumerator);

	bool isEnable() const override;

	void Enable() override;

	void Disable() override;

	std::optional<Color> GetColor() const override;

	void SetColor(Color color) override;

private:
	FillGroupEnumerator m_enumerator;
};
