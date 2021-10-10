#include "src/Designer/CDesigner.h"
#include "src/PictureDraft/CPictureDraft.h"
#include "src/ShapeFactory/CShapeFactory.h"
#include "src/Painter/CPainter.h"
#include "src/Canvas/CCanvas.h"
#include <iostream>

int main()
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CPictureDraft pictureDraft = designer.CreateDraft(std::cin);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Result");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(255, 255, 255));

		CPainter::DrawPicture(pictureDraft, canvas);

		window.display();
	}
}
