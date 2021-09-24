#pragma once
#include "../Observer/Observer.h"
#include <iostream>
#include <fstream>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info = { GetTemperature(), GetHumidity(), GetPressure() };

		return info;
	}

private:
	double m_temperature = 0;
	double m_humidity = 0;
	double m_pressure = 760;
};

class CStats
{
public:
	void Update(const SWeatherInfo& data)
	{
		m_temperature.Update(data.temperature);
		m_humidity.Update(data.humidity);
		m_pressure.Update(data.pressure);
	}

	void ToString(std::ostream& output)
	{
		output << "Temperature: " + m_temperature.ToString() << std::endl;
		output << "Humidity: " + m_humidity.ToString() << std::endl;
		output << "Pressure: " + m_pressure.ToString() << std::endl;
	}

private:
	CStatisticData m_temperature;
	CStatisticData m_humidity;
	CStatisticData m_pressure;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(const CWeatherData& observableIn, const CWeatherData& observableOut, std::ostream& output)
		: m_observableIn(observableIn)
		, m_observableOut(observableOut)
		, m_output(output)
	{
	}

private:
	void Update(const SWeatherInfo& data, const IObservable<SWeatherInfo>& observable) override
	{
		if  (&observable == &m_observableIn)
		{
			m_statisticOfInObserver.Update(data);
			m_statisticOfInObserver.ToString(this->m_output);
		}

		if  (&observable == &m_observableOut)
		{
			m_statisticOfOutObserver.Update(data);
			m_statisticOfOutObserver.ToString(this->m_output);
		}
	}

	const CWeatherData& m_observableIn;
	const CWeatherData& m_observableOut;

	CStats m_statisticOfInObserver;
	CStats m_statisticOfOutObserver;

	std::ostream& m_output;
};
