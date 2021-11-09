#pragma once
#include "../IBorderStyle/IBorderStyle.h"

typedef std::function<void(IBorderStyle& style)> BorderStyleEnumerator;

typedef std::function<void(BorderStyleEnumerator)> BorderGroupEnumerator;

class CBorderGroupStyle : public IBorderStyle
{
public:
	CBorderGroupStyle(BorderGroupEnumerator& enumerator);

	void SetThickness(double thickness) override;

	std::optional<double> GetThickness() const override;

	bool isEnable() const override;

	void Enable() override;

	void Disable() override;

	std::optional<Color> GetColor() const override;

	void SetColor(Color color) override;

private:
	BorderGroupEnumerator m_enumerator;
};
