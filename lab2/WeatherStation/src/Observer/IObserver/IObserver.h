#pragma once

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;

	virtual ~IObserver() = default;
};