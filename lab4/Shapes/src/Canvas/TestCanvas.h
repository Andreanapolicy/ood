#pragma once
#include "ICanvas.h"
#include <vector>
#include <string>

class TestCanvas : public ICanvas
{
public:
	void SetColor(const Color& color) override
	{
		m_result.push_back("set color");
	}

	void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) override
	{
		m_result.push_back("draw line");

	}

	void DrawEllipse(const CPoint& centerPoint, const int widthRadius, const int heightRadius) override
	{
		m_result.push_back("draw ellipse");

	}

	std::vector<std::string> GetResult() const
	{
		return m_result;
	}
private:
	std::vector<std::string> m_result = {};
};