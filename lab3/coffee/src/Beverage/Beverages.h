#pragma once
#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription() const override final
	{
		return m_description;
	}

protected:
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
			m_description = "Standard Cappuccino";
			m_cost = 80;
			break;
		case CoffeePortion::Double:
			m_description = "Double Cappuccino";
			m_cost = 120;
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	int m_cost;
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
			m_description = "Standard Latte";
			m_cost = 90;
			break;
		case CoffeePortion::Double:
			m_description = "Double Latte";
			m_cost = 130;
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	int m_cost;
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
			m_description = "White Tea";
			break;
		case TeaType::Black:
			m_description = "Black Tea";
			break;
		case TeaType::Green:
			m_description = "Green Tea";
			break;
		case TeaType::Yellow:
			m_description = "Yellow Tea";
			break;
		}
	}

	double GetCost() const override
	{
		return 30;
	}
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
			m_description = "Small Milkshake";
			m_cost = 50;
			break;
		case MilkshakePortion::Medium:
			m_description = "Medium Milkshake";
			m_cost = 60;
			break;
		case MilkshakePortion::Big:
			m_description = "Big Milkshake";
			m_cost = 80;
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	int m_cost;
};