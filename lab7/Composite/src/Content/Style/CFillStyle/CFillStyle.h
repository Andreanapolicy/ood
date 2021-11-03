#pragma once
#include "../IStyle/IStyle.h"

class CFillStyle : public IStyle
{
public:
	CFillStyle();

	bool isEnable() const override;

	void Enable() override;

	void Disable() override;

	Color GetColor() const override;

	void SetColor(Color color) override;

private:
	bool m_enable;
	Color m_color;
};
