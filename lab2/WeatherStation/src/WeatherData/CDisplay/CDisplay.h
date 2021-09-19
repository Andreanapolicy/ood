#pragma once
#include "../SWeatherInfo/SWeatherInfo.h"
#include "../../Observer/IObserver/IObserver.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	void Update(const SWeatherInfo& data) override;
};