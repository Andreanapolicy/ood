#include "src/app/App.h"
#include <iostream>

int main()
{
	std::cout << "Should we use new API (y)?" << std::endl;
	std::string userInput;
	if (std::cin >> userInput && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();

		return 0;
	}

	app::PaintPictureOnCanvas();

	return 0;
}