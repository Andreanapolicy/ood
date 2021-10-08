#pragma once
#include "../Color/Color.h"

class CShape
{
public:
    CShape(const Color& color)
        : m_color(color)
    {
    }

    Color GetColor() const
    {
        return m_color;
    }

    virtual void Draw(ICanvas& canvas) = 0;

private:
    Color m_color;
};