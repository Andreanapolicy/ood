#pragma once
#include "../Observer/Observer.h"
#include <iostream>
#include <fstream>
#include <cmath>

struct SWindInfo
{
	double direction = 0;
	double speed = 0;
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	SWindInfo wind;
};

class CStatisticWindDirectionData
{
public:
	void Update(double data)
	{
		this->m_sinSum = this->m_sinSum + std::sin(this->ToRadians(data));
		this->m_cosSum = this->m_cosSum + std::cos(this->ToRadians(data));

		auto x = ToDegrees(std::atan2(m_sinSum, m_cosSum)) + 360;
		this->m_average = std::fmod(x, 360);
	}

	std::string ToString() const
	{
		return "average direction: " + std::to_string(m_average);
	}

private:
	double ToRadians(double degrees) const
	{
		return M_PI * degrees / 180;
	}

	double ToDegrees(double radians) const
	{
		return 180 * radians / M_PI;
	}

	double m_sinSum = 0;
	double m_cosSum = 0;
	double m_average = 0;
};

class CStatisticData
{
public:
	void Update(double data)
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

	std::string ToString() const
	{
		return "min: " + std::to_string(m_min) + ", max: " + std::to_string(m_max) + ", average: " + std::to_string(m_sum / m_count);
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_sum = 0;
	unsigned m_count = 0;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature() const
	{
		return m_temperature;
	}

	double GetHumidity() const
	{
		return m_humidity;
	}

	double GetPressure() const
	{
		return m_pressure;
	}

	SWindInfo GetWind() const
	{
		return m_wind;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double direction, double speed)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_wind = {direction, speed};

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info = { GetTemperature(), GetHumidity(), GetPressure(), GetWind() };

		return info;
	}

private:
	double m_temperature = 0;
	double m_humidity = 0;
	double m_pressure = 760;
	SWindInfo m_wind;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(std::ostream& output)
		: m_output(output)
	{
	}

private:
	void Update(const SWeatherInfo& data) override
	{
		this->m_temperature.Update(data.temperature);
		this->m_humidity.Update(data.humidity);
		this->m_pressure.Update(data.pressure);
		this->m_windSpeed.Update(data.wind.speed);
		this->m_windDirection.Update(data.wind.direction);

		this->m_output << "Temperature: " << this->m_temperature.ToString() << std::endl;
		this->m_output << "Humidity: " << this->m_humidity.ToString() << std::endl;
		this->m_output << "Pressure: " << this->m_pressure.ToString() << std::endl;
		this->m_output << "Wind: speed: " << this->m_windSpeed.ToString() << ", " << this->m_windDirection.ToString() << std::endl;
	}

	CStatisticData m_temperature;
	CStatisticData m_humidity;
	CStatisticData m_pressure;
	CStatisticData m_windSpeed;
	CStatisticWindDirectionData m_windDirection;

	std::ostream& m_output;
};
