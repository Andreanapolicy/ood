#pragma once
#include "../../WeatherData/SWeatherInfo/SWeatherInfo.h"
#include "../IObserver/IObserver.h"
#include "../IObservable/IObservable.h"

class CDestructionTestObserver : public IObserver<SWeatherInfo>
{
public:
	typedef IObservable<SWeatherInfo> ObservableType;

	CDestructionTestObserver(ObservableType& observable)
		: m_observable(&observable)
	{
	}

private:
	void Update(SWeatherInfo const& data)
	{
		m_observable->RemoveObserver(*this);

		std::cout << "Temp: " << data.temperature << std::endl;
		std::cout << "Hum: " << data.humidity << std::endl;
		std::cout << "Pressure: " << data.pressure << std::endl;
		std::cout << "===============" << std::endl;
	}

	ObservableType* m_observable;
};