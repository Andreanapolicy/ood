#pragma once
#include <climits>
#include <algorithm>

class CStatisticData
{
public:
	void Update(double data);

	std::string ToString() const;

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_sum = 0;
	unsigned m_count = 0;
};
