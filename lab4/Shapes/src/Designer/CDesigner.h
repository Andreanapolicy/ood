#pragma once
#include "../ShapeFactory/IShapeFactory.h"
#include "./IDesigner.h"
#include <iostream>
#include "../ShapeFactory/Exception/InvalidNameOfShapeException.h"
#include "../ShapeFactory/Exception/InvalidParamException.h"
#include "../ShapeFactory/Exception/InvalidParamsCountException.h"

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactory& factory)
		: m_factory(factory)
	{
	}

	CPictureDraft CreateDraft(std::istream& input) const override
	{
		CPictureDraft pictureDraft;

		std::string command;

		while (std::getline(input, command) && command != "end")
		{
			if (command == "help")
			{
				std::cout << "rectangle <color> <left top point x> <left top point y> <width> <height>" << std::endl
					<< "triangle <color> <first vertex x> <first vertex y> <second vertex x> <second vertex y> <third vertex x> <third vertex y>" << std::endl
					<< "ellipse <color> <center point x> <center point y> <horizontal radius> <vertical radius>" << std::endl
					<< "regular_polygon <color> <vertex count> <center point x> <center point y> <radius>" << std::endl;

				continue;
			}
			try
			{
				pictureDraft.AddShape(m_factory.CreateShape(command));
			}
			catch (const std::exception& exception)
			{
				std::cout << "Error: " << exception.what() << std::endl;
			}
		}

		return pictureDraft;
	}

private:
	IShapeFactory& m_factory;
};