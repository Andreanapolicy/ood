#pragma once
#include "../IBorderStyle/IBorderStyle.h"

typedef std::function<void(BorderStyleEnumerator)> BorderGroupEnumerator;

class CBorderGroupStyle : public IBorderStyle
{
public:
	CBorderGroupStyle(BorderGroupEnumerator& enumerator);

	void SetThickness(double thickness) override;

	double GetThickness() const override;

	bool isEnable() const override;

	void Enable() override;

	void Disable() override;

	Color GetColor() const override;

	void SetColor(Color color) override;

private:
	BorderGroupEnumerator m_enumerator;
};
