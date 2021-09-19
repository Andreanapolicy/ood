#include "CStatisticData.h"

void CStatisticData::Update(double data)
{
	if (m_min > data)
	{
		m_min = data;
	}

	if (m_max < data)
	{
		m_max = data;
	}

	m_sum += data;
	m_count++;
}

std::string CStatisticData::ToString() const
{
	return "min: " + std::to_string(m_min) + ", max: " + std::to_string(m_max) + ", average: " + std::to_string(m_sum / m_count);
}