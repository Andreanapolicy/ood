#pragma once
#include "../IObserver/IObserver.h"
#include "../../WeatherData/SWeatherInfo/SWeatherInfo.h"

class CPriorityTestObserver : public IObserver<SWeatherInfo>
{
public:
	CPriorityTestObserver(int id, std::ostream& output)
		: m_id(id)
		, m_output(output)
	{
	}

	void Update(SWeatherInfo const& data) override
	{
		m_output << m_id;
	}

private:
	int m_id;
	std::ostream& m_output;
};