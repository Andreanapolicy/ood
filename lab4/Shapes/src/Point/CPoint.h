#pragma once

class CPoint
{
public:
    CPoint(const double x, const double y)
        : m_x(x)
        , m_y(y)
    {
    }

	bool operator==(const CPoint& point) const
	{
		return this->m_x == point.m_x && this->m_y == point.m_y;
	}

    double getX() const
    {
        return m_x;
    }

	double getY() const
    {
        return m_y;
    }

private:
	double m_x;
	double m_y;
};
