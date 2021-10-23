#include "./src/Client/CEditor/CEditor.h"
#include <iostream>

int main()
{
	CEditor editor(std::cin, std::cout);

	editor.Run();

	return 0;
}
