#pragma once
#include "IBeverage.h"
#include <map>

class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription() const override
	{
		return m_description;
	}

private:
	std::string m_description;
};

class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		: CBeverage(description)
	{
	}

	double GetCost() const override
	{
		return 60;
	}
};

enum class CoffeePortion
{
	Standard,
	Double
};

class CCappuccino : public CCoffee
{
public:
	CCappuccino(const CoffeePortion& cappuccinoPortion)
		: CCoffee("Cappuccino")
	{
		switch (cappuccinoPortion)
		{
		case CoffeePortion::Standard:
			m_description = "Standard";
			m_cost = 80;
			break;
		case CoffeePortion::Double:
			m_description = "Double";
			m_cost = 120;
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

	std::string GetDescription() const override
	{
		return m_description + ' ' + CBeverage::GetDescription();
	}

private:
	std::string m_description;

	double m_cost;
};

class CLatte : public CCoffee
{
public:
	CLatte(const CoffeePortion& lattePortion)
		: CCoffee("Latte")
	{
		switch (lattePortion)
		{
		case CoffeePortion::Standard:
			m_cost = 90;
			m_description = "Standard";
			break;
		case CoffeePortion::Double:
			m_cost = 130;
			m_description = "Double";
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

	std::string GetDescription() const override
	{
		return m_description + ' ' + CBeverage::GetDescription();
	}

private:
	std::string m_description;

	double m_cost;
};

enum class TeaType
{
	White,
	Black,
	Green,
	Yellow
};

class CTea : public CBeverage
{
public:
	CTea(const TeaType& teaType)
		: CBeverage("Tea")
	{
		switch (teaType)
		{
		case TeaType::White:
			m_description = "White";
			break;
		case TeaType::Black:
			m_description = "Black";
			break;
		case TeaType::Green:
			m_description = "Green";
			break;
		case TeaType::Yellow:
			m_description = "Yellow";
			break;
		}
	}

	double GetCost() const override
	{
		return 30;
	}

	std::string GetDescription() const override
	{
		return m_description + ' ' + CBeverage::GetDescription();
	}

private:
	std::string m_description;
};

enum class MilkshakePortion
{
	Small,
	Medium,
	Big
};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(const MilkshakePortion& milkshakePortion)
		: CBeverage("Milkshake")
	{
		switch (milkshakePortion)
		{
		case MilkshakePortion::Small:
			m_description = "Small";
			m_cost = 50;
			break;
		case MilkshakePortion::Medium:
			m_description = "Medium";
			m_cost = 60;
			break;
		case MilkshakePortion::Big:
			m_description = "Big";
			m_cost = 80;
			break;
		}
	}

	std::string GetDescription() const override
	{
		return m_description + ' ' + CBeverage::GetDescription();
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	std::string m_description;

	double m_cost;
};