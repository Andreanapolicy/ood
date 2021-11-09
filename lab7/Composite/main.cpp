#include "src/Application/Canvas/CCanvas/CCanvas.h"
#include "src/Application/Slide/CSlide/CSlide.h"
#include "src/Content/Group/CGroup/CGroup.h"
#include "src/Content/Shape/CEllipse/CEllipse.h"
#include "src/Content/Shape/CRectangle/CRectangle.h"
#include "src/Content/Shape/CTriangle/CTriangle.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

std::shared_ptr<IShape> GetMask()
{
	auto mainPart = std::make_shared<CRectangle>(PointD{ 270, 305 }, 260, 100);
	mainPart->GetFillStyle()->Enable();
	mainPart->GetFillStyle()->SetColor(0xabf5f2FF);
	mainPart->GetLineStyle()->Enable();
	mainPart->GetLineStyle()->SetColor(0xFFFFFFFF);

	auto leftConnector = std::make_shared<CRectangle>(PointD{ 253, 305 }, 17, 5);
	leftConnector->GetFillStyle()->Enable();
	leftConnector->GetFillStyle()->SetColor(0xFFFFFFFF);

	auto rightConnector = std::make_shared<CRectangle>(PointD{ 530, 305 }, 17, 5);
	rightConnector->GetFillStyle()->Enable();
	rightConnector->GetFillStyle()->SetColor(0xFFFFFFFF);

	auto mask = std::make_shared<CGroup>();
	mask->InsertShape(mainPart, 0);
	mask->InsertShape(leftConnector, 1);
	mask->InsertShape(rightConnector, 2);

	return mask;
}

std::shared_ptr<IShape> GetGlasses()
{
	auto rightEye = std::make_shared<CTriangle>(PointD{ 430, 230 }, PointD{ 465, 290 }, PointD{ 500, 230 });
	rightEye->GetFillStyle()->Enable();
	rightEye->GetFillStyle()->SetColor(0x000000a0);
	rightEye->GetLineStyle()->SetColor(0x000000FF);
	rightEye->GetLineStyle()->SetThickness(2);
	rightEye->GetLineStyle()->Enable();

	auto leftEye = std::make_shared<CTriangle>(PointD{ 300, 230 }, PointD{ 335, 290 }, PointD{ 370, 230 });
	leftEye->GetFillStyle()->Enable();
	leftEye->GetFillStyle()->SetColor(0x000000a0);
	leftEye->GetLineStyle()->SetColor(0x000000FF);
	leftEye->GetLineStyle()->SetThickness(2);
	leftEye->GetLineStyle()->Enable();

	auto leftConnector = std::make_shared<CRectangle>(PointD{ 250, 255 }, 70, 5);
	leftConnector->GetFillStyle()->Enable();
	leftConnector->GetFillStyle()->SetColor(0x000000FF);

	auto rightConnector = std::make_shared<CRectangle>(PointD{ 480, 255 }, 70, 5);
	rightConnector->GetFillStyle()->Enable();
	rightConnector->GetFillStyle()->SetColor(0x000000FF);

	auto middleConnector = std::make_shared<CRectangle>(PointD{ 350, 255 }, 100, 5);
	middleConnector->GetFillStyle()->Enable();
	middleConnector->GetFillStyle()->SetColor(0x000000FF);

	auto glasses = std::make_shared<CGroup>();
	glasses->InsertShape(leftEye, 0);
	glasses->InsertShape(rightEye, 1);
	glasses->InsertShape(leftConnector, 2);
	glasses->InsertShape(middleConnector, 3);
	glasses->InsertShape(rightConnector, 4);

	return glasses;
}

std::shared_ptr<IShape> GetEyes()
{
	auto leftSclera = std::make_shared<CEllipse>(PointD{ 465, 345 }, 35, 30);
	leftSclera->GetFillStyle()->Enable();
	leftSclera->GetFillStyle()->SetColor(0xFFFFFFFF);
	leftSclera->GetLineStyle()->SetColor(0x000000FF);
	leftSclera->GetLineStyle()->SetThickness(1);
	leftSclera->GetLineStyle()->Enable();

	auto leftPupil = std::make_shared<CEllipse>(PointD{ 465, 345 }, 10, 10);
	leftPupil->GetFillStyle()->Enable();
	leftPupil->GetFillStyle()->SetColor(0x31736bFF);
	leftPupil->GetLineStyle()->SetColor(0x484f00FF);
	leftPupil->GetLineStyle()->SetThickness(1);
	leftPupil->GetLineStyle()->Enable();

	auto leftEye = std::make_shared<CGroup>();
	leftEye->InsertShape(leftSclera, 0);
	leftEye->InsertShape(leftPupil, 1);

	auto rightSclera = std::make_shared<CEllipse>(PointD{ 335, 345 }, 35, 30);
	rightSclera->GetFillStyle()->Enable();
	rightSclera->GetFillStyle()->SetColor(0xFFFFFFFF);
	rightSclera->GetLineStyle()->SetColor(0x000000FF);
	rightSclera->GetLineStyle()->SetThickness(1);
	rightSclera->GetLineStyle()->Enable();

	auto rightPupil = std::make_shared<CEllipse>(PointD{ 335, 345 }, 10, 10);
	rightPupil->GetFillStyle()->Enable();
	rightPupil->GetFillStyle()->SetColor(0x31736bFF);
	rightPupil->GetLineStyle()->SetColor(0x484f00FF);
	rightPupil->GetLineStyle()->SetThickness(1);
	rightPupil->GetLineStyle()->Enable();

	auto rightEye = std::make_shared<CGroup>();
	rightEye->InsertShape(rightSclera, 0);
	rightEye->InsertShape(rightPupil, 1);

	auto eyes = std::make_shared<CGroup>();
	eyes->InsertShape(rightEye, 0);
	eyes->InsertShape(leftEye, 1);

	return eyes;
}

std::shared_ptr<IShape> GetBigFace()
{
	auto head = std::make_shared<CEllipse>(PointD{ 400, 300 }, 150, 150);
	head->GetFillStyle()->Enable();
	head->GetFillStyle()->SetColor(0xf5c1abFF);
	head->GetLineStyle()->SetColor(0x000000FF);
	head->GetLineStyle()->SetThickness(2);
	head->GetLineStyle()->Enable();

	auto eyes = GetEyes();
	auto glasses = GetGlasses();
	auto mask = GetMask();

	auto bigFace = std::make_shared<CGroup>();
	bigFace->InsertShape(head, 0);
	bigFace->InsertShape(eyes, 1);
	bigFace->InsertShape(glasses, 2);
	bigFace->InsertShape(mask, 3);

	return bigFace;
}

std::shared_ptr<IShape> GetBackground()
{
	auto firstRectangle = std::make_shared<CRectangle>(PointD{ 0, 0 }, 200, 600);
	firstRectangle->GetFillStyle()->Enable();
	firstRectangle->GetFillStyle()->SetColor(0x353a42FF);

	auto secondRectangle = std::make_shared<CRectangle>(PointD{ 200, 0 }, 200, 600);
	secondRectangle->GetFillStyle()->Enable();
	secondRectangle->GetFillStyle()->SetColor(0x293d2eFF);

	auto thirdRectangle = std::make_shared<CRectangle>(PointD{ 400, 0 }, 200, 600);
	thirdRectangle->GetFillStyle()->Enable();
	thirdRectangle->GetFillStyle()->SetColor(0x393d29FF);

	auto fourthRectangle = std::make_shared<CRectangle>(PointD{ 600, 0 }, 200, 600);
	fourthRectangle->GetFillStyle()->Enable();
	fourthRectangle->GetFillStyle()->SetColor(0x3d2f29FF);

	auto background = std::make_shared<CGroup>();
	background->InsertShape(firstRectangle, 0);
	background->InsertShape(secondRectangle, 1);
	background->InsertShape(thirdRectangle, 2);
	background->InsertShape(fourthRectangle, 3);

	return background;
}

std::shared_ptr<CSlide> CreateSlide ()
{
	auto slide = std::make_shared<CSlide>(800, 600);

	slide->InsertShape(GetBackground(), 0);
	slide->InsertShape(GetBigFace(), 1);
	return slide;
}

int main()
{
	auto slide = CreateSlide();

	auto width = (unsigned int) slide->GetWidth();
	auto height = (unsigned int) slide->GetHeight();

	sf::RenderWindow renderWindow(sf::VideoMode(width, height), "Result");
	CCanvas canvas(renderWindow);

	while (renderWindow.isOpen())
	{
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}

		renderWindow.clear(sf::Color::White);
		slide->Draw(canvas);
		renderWindow.display();
	}
}
