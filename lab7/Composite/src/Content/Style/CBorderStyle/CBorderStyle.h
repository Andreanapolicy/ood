#pragma once
#include "../IBorderStyle/IBorderStyle.h"

class CBorderStyle : public IBorderStyle
{
public:
	CBorderStyle();

	void SetThickness(double thickness) override;

	std::optional<double> GetThickness() const override;

	bool isEnable() const override;

	void Enable() override;

	void Disable() override;

	std::optional<Color> GetColor() const override;

	void SetColor(Color color) override;

private:
	bool m_enable;
	Color m_color;
	double m_thickness;
};
