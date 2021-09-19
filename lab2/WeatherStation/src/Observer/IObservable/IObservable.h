#pragma once
#include "../IObserver/IObserver.h"

template <typename T>
class IObservable
{
public:
	virtual void RegisterObserver(IObserver<T>& observer) = 0;

	virtual void NotifyObservers() = 0;

	virtual void RemoveObserver(IObserver<T>& observer) = 0;

	virtual ~IObservable() = default;
};