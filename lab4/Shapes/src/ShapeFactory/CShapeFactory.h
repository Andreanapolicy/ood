#pragma once
#include "../Color/Color.h"
#include "../Point/CPoint.h"
#include "../Shape/CEllipse.h"
#include "../Shape/CRectangle.h"
#include "../Shape/CRegularPolygon.h"
#include "../Shape/CTriangle.h"
#include "./Exception/InvalidNameOfShapeException.h"
#include "./Exception/InvalidParamException.h"
#include "./Exception/InvalidParamsCountException.h"
#include "./IShapeFactory.h"
#include <functional>
#include <map>
#include <vector>

class CShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(const std::string& description) override
	{
		std::vector<std::string> params = GetParams(description);
		if (params.empty())
		{
			throw InvalidParamsCountException("Error, wrong count of params");
		}

		auto it = SHAPES_COMMAND.find(params[0]);
		if (it != SHAPES_COMMAND.end())
		{
			return it->second(params);
		}

		throw InvalidNameOfShapeException("Error, wrong name of shape");
	}

private:
	Color GetColor(const std::string& color)
	{
		auto it = COLOR_MAP.find(color);

		if (it != COLOR_MAP.end())
		{
			return it->second;
		}

		throw InvalidParamException("Error, wrong color");
	}

	std::vector<std::string> static GetParams(const std::string& line)
	{
		std::istringstream iss(line);
		std::vector<std::string> params;
		std::string param;

		while (iss >> param)
		{
			params.push_back(param);
		}

		return params;
	}

	std::unique_ptr<CShape> CreateRectangle(const std::vector<std::string>& args)
	{
		if (args.size() != 6)
		{
			throw InvalidParamsCountException("Error, wrong params count for rectangle");
		}

		Color color = GetColor(args[1]);
		CPoint leftTopPoint = {std::stod(args[2]), std::stod(args[3])};
		auto width = std::stod(args[4]);
		auto height = std::stod(args[5]);

		return std::make_unique<CRectangle>(color, leftTopPoint, width, height);
	}

	std::unique_ptr<CShape> CreateTriangle(const std::vector<std::string>& args)
	{
		if (args.size() != 8)
		{
			throw InvalidParamsCountException("Error, wrong params count for triangle");
		}

		Color color = GetColor(args[1]);
		CPoint firstVertex = {std::stod(args[2]), std::stod(args[3])};
		CPoint secondVertex = {std::stod(args[4]), std::stod(args[5])};
		CPoint thirdVertex = {std::stod(args[6]), std::stod(args[7])};

		return std::make_unique<CTriangle>(color, firstVertex, secondVertex, thirdVertex);
	}

	std::unique_ptr<CShape> CreateEllipse(const std::vector<std::string>& args)
	{
		if (args.size() != 6)
		{
			throw InvalidParamsCountException("Error, wrong params count for ellipse");
		}

		Color color = GetColor(args[1]);
		CPoint centerPoint = {std::stod(args[2]), std::stod(args[3])};
		auto widthRadius = std::stod(args[4]);
		auto heightRadius = std::stod(args[5]);

		return std::make_unique<CEllipse>(color, centerPoint, widthRadius, heightRadius);
	}

	std::unique_ptr<CShape> CreateRegularPolygon(const std::vector<std::string>& args)
	{
		if (args.size() != 6)
		{
			throw InvalidParamsCountException("Error, wrong params count for regular polygon");
		}

		Color color = GetColor(args[1]);
		int vertexCount = std::atoi(args[2].c_str());
		CPoint center = {std::stod(args[3]), std::stod(args[4])};
		auto radius = std::stod(args[5]);

		return std::make_unique<CRegularPolygon>(color, vertexCount, center, radius);
	}

	using Handler = std::function<std::unique_ptr<CShape>(const std::vector<std::string>& args)>;

	using ActionMap = std::map<std::string, Handler>;

	const ActionMap SHAPES_COMMAND = {
		{"rectangle", [this](const std::vector<std::string>& args) { return CreateRectangle(args); } },
		{"triangle", [this](const std::vector<std::string>& args) { return CreateTriangle(args); } },
		{"ellipse", [this](const std::vector<std::string>& args) { return CreateEllipse(args); } },
		{"regular_polygon", [this](const std::vector<std::string>& args) { return CreateRegularPolygon(args); } },
	};

	const std::map<std::string, Color> COLOR_MAP = {
		{"green", Color::Green},
		{"red", Color::Red},
		{"blue", Color::Blue},
		{"yellow", Color::Yellow},
		{"pink", Color::Pink},
		{"black", Color::Black},
	};
};