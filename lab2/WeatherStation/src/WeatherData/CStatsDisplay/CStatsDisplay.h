#pragma once
#include "../../Observer/IObserver/IObserver.h"
#include "../CStatisticData/CStatisticData.h"
#include "../SWeatherInfo/SWeatherInfo.h"
#include <iostream>

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(const SWeatherInfo& data) override;

	CStatisticData m_temperature;
	CStatisticData m_humidity;
	CStatisticData m_pressure;
};
