#include "CStatsDisplay.h"

void CStatsDisplay::Update(const SWeatherInfo& data)
{
	m_temperature.Update(data.temperature);
	m_humidity.Update(data.humidity);
	m_pressure.Update(data.pressure);

	std::cout << "Temperature: " << m_temperature.ToString() << std::endl;
	std::cout << "Humidity: " << m_humidity.ToString() << std::endl;
	std::cout << "Pressure: " << m_pressure.ToString() << std::endl;
	std::cout << "=======================" << std::endl;
}