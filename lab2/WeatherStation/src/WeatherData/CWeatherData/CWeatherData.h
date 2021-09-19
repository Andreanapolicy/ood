#pragma once
#include "../../Observer/CObservable/CObservable.h"
#include "../CStatisticData/CStatisticData.h"
#include "../SWeatherInfo/SWeatherInfo.h"

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature() const;

	double GetHumidity() const;

	double GetPressure() const;

	void MeasurementsChanged();

	void SetMeasurements(double temp, double humidity, double pressure);

protected:
	SWeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0;
	double m_humidity = 0;
	double m_pressure = 760;
};
