#pragma once
#include <map>

template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, const IObservable<T>& observer) = 0;

	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;

	virtual void NotifyObservers() = 0;

	virtual void RemoveObserver(IObserver<T>& observer) = 0;

	virtual ~IObservable() = default;
};

template <typename T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, const int priority) override
	{
		m_observers.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		std::multimap<int, ObserverType*> observers = m_observers;

		for (auto it = observers.begin(); it != observers.end(); ++it)
		{
			it->second->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			if (it->second == &observer)
			{
				m_observers.erase(it);
				break;
			}
		}
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	std::multimap<int, ObserverType*> m_observers = {};
};